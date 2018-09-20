//DHT11 2
//MQ2 3
//Light A2
//Rain A3
//Batt A0

#include "DHT.h"

#define DHTPIN 2
#define BATT A0

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned char pack[100];

unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

int lux(int sensorLight){
  float Vout = sensorLight*3.3/1023;
  float ldr = Vout * 10.0 / (4.7 - Vout);
  return pow(ldr, -1.25) * 562.34;
}

void setup() {
  Serial.begin(38400);
  dht.begin();
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int batt = map(analogRead(A0), 410, 510, 0, 100);
  if (batt > 100) batt = 100;

  sprintf(pack, "ssm1,%d,Temp:%d,Hum:%d,Gas:%d,Light:%d", batt, t, h, analogRead(A2), lux(analogRead(A3)));
  unsigned long hashValue = hash(pack);
  Serial.print(hashValue);
  Serial.print("|");
  Serial.println((char*)pack);
  delay(5000);
}

//hashAddress = 5381;
//for (counter = 0; word[counter]!='\0'; counter++){
//    hashAddress = ((hashAddress << 5) + hashAddress) + word[counter];
//}
