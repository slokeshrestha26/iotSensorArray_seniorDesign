/* This sketch implements the waistband module of the wearable framework

Authors: Sloke Shrestha, Lloyd McGrath, Cody Conder

University of Texas at Tyler © 2022. 
Senior Design Project

*/
#include "classify_data.h"

// length of data in an array
#define DATA_LENGTH_ACC 7800
#define DATA_LENGTH_HR 300

#define STRESS_CLASS 1 //if the classification is 1, then this signifies that stress was detected.

void initializeBluetooth();
void sendAlert();
void getData();

//blocks of data bluetooth
int bluetoothDataX[1560] = [];
int bluetoothDataY[1560] = [];
int bluetoothDataZ[1560] = [];
int bluetoothDataHR[60] = [];
int bluetoothDataEpoch[1560] = [];

//blocks of data 1 Minute
int minute1DataX[1560] = [];
int minute1DataY[1560] = [];
int minute1DataZ[1560] = [];
int minute1DataHR[60] = [];
int minute1DataEpoch[1560] = [];

//blocks of data 2 Minute
int minute2DataX[1560] = [];
int minute2DataY[1560] = [];
int minute2DataZ[1560] = [];
int minute2DataHR[60] = [];
int minute2DataEpoch[1560] = [];

//blocks of data 3 Minute
int minute3DataX[1560] = [];
int minute3DataY[1560] = [];
int minute3DataZ[1560] = [];
int minute3DataHR[60] = [];
int minute3DataEpoch[1560] = [];

//blocks of data 4 Minute
int minute4DataX[1560] = [];
int minute4DataY[1560] = [];
int minute4DataZ[1560] = [];
int minute4DataHR[60] = [];
int minute4DataEpoch[1560] = [];

//blocks of data 5 Minute
int minute5DataX[1560] = [];
int minute5DataY[1560] = [];
int minute5DataZ[1560] = [];
int minute5DataHR[60] = [];
int minute5DataEpoch[1560] = [];

//blocks of data for ML. This array goes directly to the classification subroutine.
int mlDataX[23700] = [];

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

  if(bluetoothDataX[1560]){
    for(i=0;i<=1560;i++){
      //Shifts all data in 4 minute block to 5 minute block.
      int minute5DataX[i] = minute4DataX[i];
      int minute5DataY[i] = minute4DataY[i];
      int minute5DataZ[i] = minute4DataZ[i];
      if(i <= 60){
        int minute5DataHR[i] = minute4DataHR[i];
      }
      int minute5DataEpoch[i] = minute4DataEpoch[i];

      //Shifts all data in 3 minute block to 4 minute block.
      int minute4DataX[i] = minute3DataX[i];
      int minute4DataY[i] = minute3DataY[i];
      int minute4DataZ[i] = minute3DataZ[i];
      if(i <= 60){
        int minute4DataHR[i] = minute3DataHR[i];
      }
      int minute4DataEpoch[i] = minute3DataEpoch[i];

      //Shifts all data in 2 minute block to 3 minute block.
      int minute3DataX[i] = minute2DataX[i];
      int minute3DataY[i] = minute2DataY[i];
      int minute3DataZ[i] = minute2DataZ[i];
      if(i <= 60){
        int minute3DataHR[i] = minute2DataHR[i];
      }
      int minute3DataEpoch[i] = minute2DataEpoch[i];

      //Shifts all data in 1 minute block to 2 minute block.
      int minute2DataX[i] = minute1DataX[i];
      int minute2DataY[i] = minute1DataY[i];
      int minute2DataZ[i] = minute1DataZ[i];
      if(i <= 60){
        int minute2DataHR[i] = minute1DataHR[i];
      }
      int minute2DataEpoch[i] = minute1DataEpoch[i];

      //Shifts all data in bluetooth block to 1 minute block.
      int minute1DataX[i] = bluetoothDataX[i];
      int minute1DataY[i] = bluetoothDataY[i];
      int minute1DataZ[i] = bluetoothDataZ[i];
      if(i <= 60){
        int minute1DataHR[i] = bluetoothDataHR[i];
      }
      int minute1DataEpoch[i] = bluetoothDataEpoch[i];
    }

    if(minute5DataX[1560]){
      //Do ML program with all data
      for(i=0;i<=1560;i++){

        //Puts all of X data into a single array
        mlData[i] = minute1DataX[i];
        mlData[i+1560] = minute2DataX[i];
        mlData[i+(1560*2)] = minute3DataX[i];
        mlData[i+(1560*3)] = minute4DataX[i];
        mlData[i+(1560*4)] = minute5DataX[i];
        //Nexts add Y into the ml array
        mlData[i+(1560*5)] = minute1DataY[i];
        mlData[i+(1560*6)] = minute2DataY[i];
        mlData[i+(1560*7)] = minute3DataY[i];
        mlData[i+(1560*8)] = minute4DataY[i];
        mlData[i+(1560*9)] = minute5DataY[i];
        //Nexts add Z into the ml array
        mlData[i+(1560*10)] = minute1DataZ[i];
        mlData[i+(1560*11)] = minute2DataZ[i];
        mlData[i+(1560*12)] = minute3DataZ[i];
        mlData[i+(1560*13)] = minute4DataZ[i];
        mlData[i+(1560*14)] = minute5DataZ[i];
        //Nexts add HR into the ml array
        if(i<=60){
          mlData[i+(1560*5)] = minute1DataHR[i];
          mlData[i+(1560*6)] = minute2DataHR[i];
          mlData[i+(1560*7)] = minute3DataHR[i];
          mlData[i+(1560*8)] = minute4DataHR[i];
          mlData[i+(1560*9)] = minute5DataHR[i];
        }
      }
    }
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