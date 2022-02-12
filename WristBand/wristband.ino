#include <SPI.h>
#include <SD.h>

/* Trying out SD.h
*/

File myFile;

void setup(){
  SerialUSB.begin(1200);
  //wait while SD card initializes
  while(!SerialUSB);
  SerialUSB.println("Serial Comms with computer is up .....");
  initializeSDCard();
}

void loop(){
  
}

void initializeSDCard(){

  /* Initializes the SD card by uisng the SD classsed from SD.h
  Enabled SerialUSB for debugging.
  */

  while(!SD.begin()){
    SerialUSB.println("Problem with SD card...");
  }
  SerialUSB.println("SD card is initialized");

}
