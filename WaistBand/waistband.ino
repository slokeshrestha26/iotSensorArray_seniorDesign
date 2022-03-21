#include "classify_data.h"

// length of data in an array
#define DATA_LENGTH_ACC 7800
#define DATA_LENGTH_HR 300

#define STRESS_CLASS 1 //if the classification is 1, then this signifies that stress was detected.

void initializeBluetooth();
void sendAlert();
void getData();

void setup()
{
 initializeBluetooth(); 
}

void loop(){
  double data[DATA_LENGTH_ACC] = getData(); //ONLY USING ACC DATA FOR NOW
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
