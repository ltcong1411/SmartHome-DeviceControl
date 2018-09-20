#include "U8glib.h"
#include <IRremote.h>

int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

int aValue = 0;
char b[5];

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);

  Serial.println("draw");
  Serial.println(aValue);
  sprintf(b, "%d", aValue);
  dtostrf(aValue, 0, 0, b);
  Serial.println(b);
  u8g.drawStr( 20, 27, "Living Room: ");
  u8g.drawStr( 55, 44, b);
  u8g.drawStr( 70, 44, "*C");
  //  u8g.drawStr( 0, 27, "Bed Room: ");
  //  u8g.drawStr( 95, 27, b);
  //  u8g.drawStr( 0, 44, "Kitchen: ");
  //  u8g.drawStr( 95, 44, b);
  //  u8g.drawStr( 0, 61, "Act Room: ");
  //  u8g.drawStr( 95, 61, b);
}

void readAirValue() {
  if (irrecv.decode(&results)) {
    Serial.println("Doc tu remote la: ");
    Serial.println(results.value, HEX);
//    aValue = (int)results.value;
//    Serial.println(aValue);
    switch (results.value) {
      case 0x18 :
        Serial.println("18");
        aValue = 18;
        break;
      case 0x0 :
        Serial.println("OFF");
        aValue = 0;
        break;
      case 0x19 :
        Serial.println("19");
        aValue = 19;
        break;
      case 0x20 :
        Serial.println("20");
        aValue = 20;
        break;
      case 0x21 :
        Serial.println("21");
        aValue = 21;
        break;
      case 0x22 :
        Serial.println("22");
        aValue = 22;
        break;
      case 0x23 :
        Serial.println("23");
        aValue = 23;
        break;
      case 0x24 :
        Serial.println("24");
        aValue = 24;
        break;
      case 0x25 :
        Serial.println("25");
        aValue = 25;
        break;
      case 0x26 :
        Serial.println("26");
        aValue = 26;
        break;
      case 0x27 :
        Serial.println("27");
        aValue = 27;
        break;
      case 0x28 :
        Serial.println("28");
        aValue = 28;
        break;
      case 0x29 :
        Serial.println("29");
        aValue = 29;
        break;
      case 0x30 :
        Serial.println("30");
        aValue = 30;
        break;
    }
    irrecv.resume();  // Receive the next value
  }
}

void setup(void) {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
    readAirValue();
  } while ( u8g.nextPage() );

  delay(500);
}

