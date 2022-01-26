/* This sketch implements algorithms for the wristband module in the IoT framework. 


Authors: Sloke Shrestha, Lloyd McGrath, 2022
Copyrighted by © The University of Texas at Tyler
Department of Electrical Engineering

*/

// --------------------------------------------------------------------

#include <SPI.h>
#include <TinyScreen.h> // This library is used to print sensor values to a TinyScreen
#include "BMA250.h" // Used to interface with the acceleromter Wireling, which is used to track your steps
#include <Wire.h>
#include <Wireling.h>
#include "Adafruit_DRV2605.h" // used to interface with the LRA Wireling
#include <SdFat.h> // enables data to be logged to an sd card
#include <RTCZero.h>  // enables date and time to be recorded with each sensor reading
#include <MAX30101.h> // used to interface with the pulse oximetry sensor
#include <RTCZero.h>


// SD card variables
#define FILE_BASE_NAME "worktst.csv" // Log file base name.  Must be 13 characters or less.
char fileName[13] = FILE_BASE_NAME;
SdFat SD; // File system object.
SdFile file; // Log file.

const uint8_t ANALOG_COUNT = 4; //number of analog channels
const int chipSelect = 10;

// TinyScreen Global Variables
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_8b_Black; // sets the background color to black

const int STEP_TRIGGER = 250; // The LRA Wireling will notify you of inactivity if you complete less than half of this number of steps each hour. Step % is based on this * 16 waking hours.
const int DATA_INTERVAL = 30; // data is recorded to the microSD every DATA_INTERVAL seconds
const bool DEBUG_MD = false; // if set to true, enables debug mode
const int FAST_DATA_INTERVAL = DATA_INTERVAL * 1000; // performance optimization
const int DELAY_INTERVAL = 2800; // specifies the delay between LRA pulses in ms

// heart rate and oxygen concentration variables
int heartData[2880] = {};
int32_t bufferLength = 50; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200, the lower the faster the oxygen saturation calculation
int32_t saturatedOxygen; //saturatedOxygen value
int32_t heartRate; //heart rate value


//NOTE: IS THERE A BETTER IMPLEMENTAITON FOR TIME STAMPING? 
/* Change these values to set the current time when you upload the sketch. */
const byte seconds = 10;
const byte minutes = 34;
const byte hours = 14;

/* Change these values to set the current initial date */
const byte day = 16;
const byte month = 8;
const byte year = 19;

// used to store which sensors are connected and if so, what port they are connected to. initial 0 value represents that they are not connected
 // the microphone Wireling is not used in this project, but we have included some code that will make it very easy to add if you so choose
const float memsPin = A0; // used for microphone
int pulseSensorPort = 1;
int lraSensorPort = 2;
int accelSensorPort = 3;

// used to store which sensors are connected and if so, what port they are connected to. initial 0 value represents that they are not connected
// the microphone Wireling is not used in this project, but we have included some code that will make it very easy to add if you so choose
int pulseSensorPort = 1;
int lraSensorPort = 2;
int accelSensorPort = 3;