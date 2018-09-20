#include "msp430g2553.h"
#include "intrinsics.h"
#include "string.h"
#include "stdio.h"
#include "flash.h"
//------------------------------------------------------------------------------
union reg {
    struct bit {
          unsigned char b0:1;  
          unsigned char b1:1;    
          unsigned char b2:1; 
          unsigned char b3:1;
          unsigned char b4:1;
          unsigned char b5:1;
          unsigned char b6:1;
          unsigned char b7:1;
              }_BIT;
          unsigned char _BYTE;
};
union reg* P2_DIR=(union reg*)0x2a;  //khai bao dia chi o nho
union reg* P2_OUT=(union reg*)0x29;
union reg* P2_SEL=(union reg*)0x2e;
union reg* P2_IN=(union reg*)0x28;

union reg* P1_SEL=(union reg*)0x26;
union reg* P1_DIR=(union reg*)0x22;  //khai bao dia chi o nho
union reg* P1_OUT=(union reg*)0x21;
union reg* P1_IN=(union reg*)0x20;
//==============================================================================
//DINH NGHIA GIAO TIEP DHT11:
//===dinh nghia chan cho DHT11====:
#define DHT_IN (P1_IN->_BIT.b7)
#define DHT_OUT (P1_OUT->_BIT.b7)
#define DHT_DIR (P1_DIR->_BIT.b7)
//================================
//BIEN DHT11:
unsigned char nhietdo, doam;
//==============================================================================
//CAC CHUONG TRINH GIAO TIEP DHT11:
//thu vien DHT11
unsigned char dht_get(unsigned char *tem, unsigned char *humi)
{
  
  unsigned char buffer[5]={0,0,0,0,0};
  unsigned char i,ii;
  DHT_DIR = 1;//2.4 ra
  DHT_OUT=1;
  __delay_cycles(60);
  DHT_OUT=0;
  __delay_cycles(25000);
  DHT_OUT=1;
  DHT_DIR = 0;//2.4 vao
  __delay_cycles(60);//
   if(DHT_IN) return 0;
  else while(!DHT_IN); //doi Data len 1
   __delay_cycles(60);
   if(!DHT_IN) return 0;
  else while(DHT_IN); //doi Data xuong 0
  //doc du lieu
  for(i=0;i<5;i++)
  {
    for(ii=0;ii<8;ii++)
    {
      while(!DHT_IN); // doi len 1
      __delay_cycles(50);
      if(DHT_IN)
      {
        buffer[i]|=(1<<(7-ii));
        while(DHT_IN);
      }
    }
  }
 
    *humi =   buffer[0]; 
    *tem  =   buffer[2];
   return 1;
}
//==============================================================================
/*
huong dan cac ban su dung thu vien:
cac ban muon lay gia tri humi va nhiet do thi lam nhu sau:
 - goi ham: dht_get(&nhietdo, &doam);
 - sau do xuat cac gia tri cua bien nhietdo va doam ra 7seg hoac lcd nhe!
*/
