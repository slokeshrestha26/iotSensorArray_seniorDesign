#include <SPI.h>
#include <SD.h>


/* Trying out SD.h*/

File myFile;

void setup(){
    SerialUSB.begin(115200);
    SerialUSB.println("start");
    while(!SerialUSB){
        SerialUSB.println("looking for SD card ..."); 
    }
    SerialUSB.println("Initializing SD card...");
}

void loop(){
  
}
