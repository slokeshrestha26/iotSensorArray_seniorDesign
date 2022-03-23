#include <SoftwareSerial.h>
#define rxPin 7
#define txPin 8
SoftwareSerial hm10(rxPin,txPin); //RX, TX 

 
void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  hm10.begin(9600);
}
 
void loop() {
  hm10.listen();
  Serial.println("Listening...");
  uint8_t c = hm10.read();
  Serial.println(c);
  Serial.println(hm10.available());
  delay(1000);
}
