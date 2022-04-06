#include <SoftwareSerial.h>a

SoftwareSerial hm10(7,8); //RX, TX 


 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hm10.begin(115200);
  
}
 
void loop() {
  
  hm10.write("AT+NOTIFY_ON0010");
  //check if data available from wristband
  while(hm10.available()){
    byte data=hm10.read();
    Serial.write(data); //modify to store/write data to intended location
  }


/*
 * //if teensy sets stress to 1, send event to wristband and set stress back to 0.
 * while(stress) {
 * hm10.write("AT+SEND_DATAWN000E1);
 * stress = 0;
 * }
 * 
 */
  //test, use code above for final implementation
  while(Serial.available()){
    byte data=Serial.read();
    hm10.write(data);
  }

}
