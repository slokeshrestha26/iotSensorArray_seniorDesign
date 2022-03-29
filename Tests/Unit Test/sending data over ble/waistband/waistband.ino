#include <SoftwareSerial.h>
#define rxPin 7
#define txPin 8
SoftwareSerial hm10(rxPin,txPin); //RX, TX 

 
void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  hm10.begin(9600);
  Serial.println("works");
}
 
void loop() {
  Serial.println(hm10.available());
  Serial.println(hm10.readString());
  delay(1000);
}
