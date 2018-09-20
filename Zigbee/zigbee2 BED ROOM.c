// ZIGBEE MODULE 2 Bedroom
// P1.7--DHT11
// P1.6--LDR
// P1.5--
// P1.4--pin
// P1.3
// P1.0
//******************************************************************/
#include "msp430g2553.h"
#include "stdio.h"
#include "Library/Clock.h"
#include "Library/UART1.h"
#include "Library/ADC.h"
#include "Library/DHT11_MSP430G2553_LIB.h"
#include "math.h"

float ldr;
int test;
int gas;
int lux;
float Vout;
int i;
int pin;
int Data1;
int j = 0;


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void truyen()
{
    // ma kiem tra loi
            char str[100] = "";
            sprintf(str, "ssm2,%d,Temp:%d,Hum:%d,Light:%d", pin, nhietdo, doam, lux);
            unsigned long hashValue = hash(str);


    for (i=0; i<3;i++)
              {
                UART_Write_Int(hashValue);
                UART_Write_String("|");
                UART_Write_String(str);
                UART_Write_Char(10);
                _delay_cycles(200000);
              }
//                _delay_cycles(2000000);
}
void laymau()
   {
            Data1=ADC10_Read_Channel(6);
            Vout = Data1*2.5/1023;
            ldr = Vout*10.0/(4.7-Vout);
            lux = pow(ldr,-1.25)*562.34;
            test = ADC10_Read_Channel(4);
            dht_get(&nhietdo, &doam);
            //gas = ADC10_Read_Channel(5);

// dung luong pin
       if (test>=800) pin =100;
       else if (test>=740 & test<800) pin=80;
       else if (test>=680 & test<740) pin=60;
       else if (test>=620 & test<680) pin=40;
       else if (test>=560 & test<620) pin=20;
       else pin=5;


   }

void main()
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watchdog
    Select_Clock(DCO_1MHZ);
    SMCLK_F=1000000;
    UART_Init();    //UART
    ADC10_Init(ON2_5V);

    P2DIR|=BIT0;
    P1REN |= BIT3; // P1.3 pullup
    P1OUT = BIT3; // P1.3 hi (pullup)
    P1IE |= BIT3; // P1.3 IRQ enabled
    P1IES |= BIT3; // P1.3 Hi/lo edge
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    CCTL0 = CCIE;                   // CCR0 interrupt enabled
    CCR0 = 65535;                 // 512 -> 1 sec, 30720 -> 1 min
    TACTL = TASSEL_2 + ID_3 + MC_1;         // ACLK, /8, upmode
    IE2 &= ~UCA0RXIE;
    __bis_SR_register(GIE);
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
CCTL0 &= ~CCIE;
IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    j +=1;
    if (j == 6){
        P2OUT|=BIT0;
        laymau();
        truyen();
        j = 0;
        P2OUT&=~BIT0;
    }
}
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
    P2OUT&=~BIT0;
    _delay_cycles(1000);
    if (UCA0RXBUF == '2')
    {
        P2OUT|=BIT0;
        laymau();
        truyen();
        _delay_cycles(100000);
        P2OUT&=~BIT0;
    }

}

