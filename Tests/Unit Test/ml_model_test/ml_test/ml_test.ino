#include "classify_data.h"

// length of data in an array
#define DATA_LENGTH 23700  //7800*3 + 300. 7800 => ACC AND 300 => HR

#define STRESS_CLASS 1 //if the classification is 1, then this signifies that stress was detected.

void initializeBluetooth();
void sendAlert();
void getData();

double data[DATA_LENGTH];

void setup()
{
 initializeBluetooth();
}

void loop(){
  int class = classifyData(data);

  if (class == STRESS_CLASS){
    sendAlert();
  }

}

//====================== FUNCITON DEFINITION==================
void initializeBluetooth(){}

void sendAlert(){} //needs bluetooth
void getData(){} //needs bluetooth

/*TODO
1. convert matlab model to c
2. make sure it compiles
3. work on bluetooth*/ 
