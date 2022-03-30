#include <SoftwareSerial.h>
#define rxPinTeensy 7
#define txPinTeensy 8

// #define rxPinMEGA 15
// #define txPinMEGA 14

SoftwareSerial hm10(rxPinTeensy,txPinTeensy); //RX, TX 
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hm10.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  while(hm10.available()){
    byte data=hm10.read();
    Serial.write(data);
  }
  while(Serial.available()){

    byte data=Serial.read();
    hm10.write(data);
  }
}
