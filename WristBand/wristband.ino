#include <SPI.h>
#include <MAX30101.h> // used to interface with the pulse oximetry sensor
#include "BMA250.h" // Used to interface with the acceleromter Wireling
#include <SdFat.h> // enables data to be logged to an sd card
#include <TinyScreen.h> // This library is used to print sensor values to a TinyScreen
#include <RTCZero.h>
#include <Wireling.h>
#include "Adafruit_DRV2605.h" // used to interface with the LRA Wireling



// function prototype
bool validatePorts();
int updatePedometer();
void createString(String &, String &, bool , int , bool &);
void validateSD(String , String , bool );
void buzzLRA();
void checkButtons(unsigned long &screenClearTime);
float normalizedCrossCorrelation(const byte First[], byte Second[], float whichArray);
void initializeSensors(int8_t port_arr[]);
void initializeSDCard();

// =================== GLOBAL VARIABLES =================//

// Sensors and Actuators
BMA250 accel_sensor; // accelerometer sensor object
MAX30101 pulseSensor = MAX30101(); // pulseOx sensor object
Adafruit_DRV2605 drv; // lra sensor object

// used to store which sensors are connected and if so, what port they are connected to. initial 0 value represents that they are not connected
// the order is in the form: {pulse sensor, lra sensor, accel sensor}
int8_t port_arr[] = {1,2,3};

// SD card variables
#define FILE_BASE_NAME "worktst.csv" // Log file base name.  Must be 13 characters or less.
char fileName[13] = FILE_BASE_NAME;
SdFat SD; // File system object.
SdFile file; // Log file.
const int DATA_INTERVAL = 30; // data is recorded to the microSD every DATA_INTERVAL seconds


const uint8_t ANALOG_COUNT = 4;
const int chipSelect = 10; // SS pin for SPI

// TinyScreen variables
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_8b_Black; // sets the background color to black

const bool DEBUG_MD = false; // if set to true, enables debug mode
const int FAST_DATA_INTERVAL = DATA_INTERVAL * 1000; // performance optimization
const int DELAY_INTERVAL = 2800; // specifies the delay between LRA pulses in ms

// Heart Rate and Pulse Ox variables
int heartData[2880] = {};
int32_t bufferLength = 50; 
int32_t heartRate; 

const byte RATE_SIZE = DATA_INTERVAL * 100; // Based on the data interval. this could take a lot of memory
byte rates[RATE_SIZE]; //heart rate Data of heart rates
int beatAvg = 0; // represents the average heart rate over the DATA_INTERVAL

int motionX = 0; // x axis motion

//RTC
RTCZero rtc;


/* Trying out SD.h
*/

void setup(){
  SerialUSB.begin(9600);
  delay(5000); // replaces the above
  Wire.begin();
  Wireling.begin();

  initializeSDCard();
  initializeSensors(port_arr);
  initializeDisplay();

  //timing setup
  rtc.begin(); // timing
}

void loop(){

}

void initializeSDCard(){

  /* Initializes the SD card by uisng the object from SdFat.h 
  */

  // Check for SD card
  SerialUSB.println("Initializing SD card...");
  if (SD.begin())
  {
    SerialUSB.println("card initialized.");

    SerialUSB.print(F("Logging to: "));
    SerialUSB.println(fileName);
    SerialUSB.println();
  }
  else
  {
    SerialUSB.println("SD Card not found, exiting program!");
    SerialUSB.println();
    delay(5000);
    while (1);
  }

}

void initializeSensors(int8_t port_arr[]){
  /*initializes sensors
  port_arr: array with the port number of pulse sensor, lra sensor, and accel sensor 
  */
  int8_t accelSensorPort = port_arr[2];
  int8_t lraSensorPort = port_arr[1];
  int8_t pulseSensorPort = port_arr[0];

  if (lraSensorPort) {
    drv.begin();
    drv.selectLibrary(1);
    drv.setMode(DRV2605_MODE_INTTRIG);
    drv.useLRA();
  }

  if (accelSensorPort) {
    // Set the cursor to the following coordinates before it prints "BMA250 Test"
    Wireling.selectPort(accelSensorPort);
    accel_sensor.begin(BMA250_range_4g, BMA250_update_time_16ms); // Sets up the BMA250 accel_sensorerometer
  }

  if (pulseSensorPort)
  {
    Wireling.selectPort(pulseSensorPort);
    pulseSensor.begin(); //Configure sensor with default settings
  }
}

void initializeDisplay(){
  // This is the setup used to initialize the TinyScreen's appearance GUI this is important.
  display.begin();
  display.setBrightness(15);
  display.setFlip(true);
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_White, background);

}
