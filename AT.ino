#include <SoftwareSerial.h>

SoftwareSerial hm10(7,8); //RX, TX 
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hm10.begin(115200);
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