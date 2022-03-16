/* Wristband Sketch for Wearable Physiology Monitoring Framework

Most of the inspiration for this sketch was taken from Fitness Tracker Sketch from TinyCircuits. Mode details are
available below. 

Wearable Physiology Monitoring Framework has two mode of operations: inference mode and data aquisition. 
Inference mode collects the data from the wrist band and sends it to the waistband for further processing. 



Written by Sloke Shrestha, Lloyd McGrath, Cody Conder Fall 2021 and Spring 2022
at University of Texas at Tyler, Tyler, USA. 

This sketch is written for the senior design project for Department of Electrical Engineering 
at UT Tyler https://www.uttyler.edu/electrical-engineering/ */


//-------------------------------------------------------------------------------
//  Fitness Tracker Sketch
//
//  The fitness tracker uses data collected from the pulse oximetry and accelerometer Wirelings
//  to count your steps, determine your sleep quality, and monitor your vital signs.
//  Abnormalities trigger an LRA buzzer, which can be felt by the user.
//  Both the raw and interpreted data is sent to a microSD card every DATA_INTERVAL seconds.
//  (You can adjust the reporting interval by changing DATA_INTERVAL on line 39.)
//  
//  Note: The pulse oximetry sensor detects your heart rate optically and the accuracy of the readings
//  is highly dependent on keeping a steady pressure between you and the sensor. 
//  The best way to maintain a steady pressure is to use a clip (as used by hospital grade pulse ox sesnors)
//  Another good way is a rubber band. We have found that fingers give the most accurate readings.
//  This project is for educational purposes only!
//
//  Written by Zachary Lee, August 2019
//  Refactoring with Updated Libraries by Laveréna Wienclaw, November 2020
//
//  TinyCircuits http://TinyCircuits.com 
//-------------------------------------------------------------------------------

#include <SPI.h>
#include <TinyScreen.h> // This library is used to print sensor values to a TinyScreen
#include "BMA250.h" // Used to interface with the acceleromter Wireling, which is used to track your steps
#include <Wire.h>
#include <Wireling.h>
#include "Adafruit_DRV2605.h" // used to interface with the LRA Wireling
#include <SdFat.h> // enables data to be logged to an sd card
#include <RTCZero.h>  // enables date and time to be recorded with each sensor reading
#include <MAX30101.h> // used to interface with the pulse oximetry sensor
#include <STBLE.h> //BLE library
#include <RTCZero.h>

// inference mode preprocessor directives
#ifndef BLE_DEBUG
#define BLE_DEBUG true
#endif

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif
#define PIPE_UART_OVER_BTLE_UART_TX_TX 0

// SD card directive
#define FILE_BASE_NAME "worktst.csv" // Log file base name.  Must be 13 characters or less.


// global variable for inference mode flag
volatile uint8_t INFERENCE_MODE = 1; //flag for inference mode (default is 1)

// inference mode variables
uint8_t ble_rx_buffer[21];
uint8_t ble_rx_buffer_len = 0;
uint8_t ble_connection_state = false;


// SD card variables
char fileName[13] = FILE_BASE_NAME;
SdFat SD; // File system object.
SdFile file; // Log file.
SdFile quartiles; // keeps track of your historical heart rate during sleep, which is used in the sleep quality calculation

const uint8_t ANALOG_COUNT = 4;
const int chipSelect = 10;

Adafruit_DRV2605 drv; // lra sensor object
MAX30101 pulseSensor = MAX30101(); // pulseOx sensor object
BMA250 accel_sensor; // accelerometer sensor object


// TinyScreen Global Variables
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_8b_Black; // sets the background color to black

const int STEP_TRIGGER = 250; // The LRA Wireling will notify you of inactivity if you complete less than half of this number of steps each hour. Step % is based on this * 16 waking hours.
const int DATA_INTERVAL = 30; // data is recorded to the microSD every DATA_INTERVAL seconds
const bool DEBUG_MD = false; // if set to true, enables debug mode
const int FAST_DATA_INTERVAL = DATA_INTERVAL * 1000; // performance optimization
const int AGE = 25; // age has a significant impact on sleep composition, so inputting your age will increase the accuracy of your sleep quality calculation
const int DELAY_INTERVAL = 2800; // specifies the delay between LRA pulses in ms

// heart rate and oxygen concentration variables
int heartData[2880] = {};
int32_t bufferLength = 50; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200, the lower the faster the oxygen saturation calculation

int32_t heartRate; //heart rate value

/* Change these values to set the current time when you upload the sketch. */
const byte seconds = 10;
const byte minutes = 34;
const byte hours = 14;

/* Change these values to set the current initial date */
const byte day = 16;
const byte month = 8;
const byte year = 19;

// used to store which sensors are connected and if so, what port they are connected to. initial 0 value represents that they are not connected
int pulseSensorPort = 1;
int lraSensorPort = 2;
int accelSensorPort = 3;

unsigned long stepTimestamps[STEP_TRIGGER] = {};
unsigned long loopStart = 0;
uint32_t doVibrate = 0;
bool firstSD = true;

RTCZero rtc;

// heart rate variables
const byte RATE_SIZE = DATA_INTERVAL * 100; // Based on the data interval. this could take a lot of memory
byte rates[RATE_SIZE]; //heartDataay of heart rates
int beatAvg = 0; // represents the average heart rate over the DATA_INTERVAL

// acc variables
int motionX = 0; // x axis motion
int motionY = 0; // y axis motion
int motionZ = 0; // z axis motion

bool stressDetected = false;

/*/*==================================Fuction prototype/*==================================*/
bool validatePorts();
int updatePedometer();
void createString(String &, String &, bool , int , bool &);
void validateSD(String , String , bool );
void buzzLRA();
void checkButtons(unsigned long &screenClearTime);
float normalizedCrossCorrelation(const byte First[], byte Second[], float whichArray);
void checkPulse();
void stressDetectedButton(unsigned long &screenClearTime);

void initialize_wireling();
void initialize_sd_card();
void intialize_bluetooth();
void intialize_lrasensor();
void initialize_accelerometer();
void initialize_pulse_sensor();
void initialize_rtc();
void initialize_display();

/*==================================MAIN SETUP AND LOOP==========================================*/
void setup(void)
{
  if (INFERENCE_MODE){
    //initialize bluetooth
    intialize_bluetooth();
  }
  else{
    // intialize sd card
    initialize_sd_card();
  }

  intialize_lrasensor();
  initialize_accelerometer();
  initialize_pulse_sensor();
  initialize_rtc();
  initialize_display();
  initialize_wireling();
}


void loop() {
  String displayString = ""; // written once in the logfile to provide column headings along with the data
  String dataString = ""; // written to the logfile every data interval seconds. does not contain headings, just csv data only. see createstring for more details
  static int emptyIntsCounter = 0;
  static unsigned long screenClearTime = millis();
  static int currentHour = rtc.getHours(); // performance optimization
  
  Wireling.selectPort(pulseSensorPort);  
  checkPulse();
  
  Wireling.selectPort(accelSensorPort);
  updatePedometer();
  createString(displayString, dataString, firstSD, currentHour, validatedPreviously); //create strings from recent data
  validateSD(dataString, displayString, firstSD); // write the strings to the SD card after validating the connection to the SD card is intact
  if(pulseSensor.update()){
    if (pulseSensor.pulseValid()) {
      beatAvg = pulseSensor.BPM();
      heartData[heartIndex] = pulseSensor.BPM();
      ++heartIndex;
    }
  }

  if(stressDetected){
    stressDetected = false;
  }
  
  checkButtons(screenClearTime); // will activate display if user presses any button except top right
  stressDetectedButton(screenClearTime); // will activate display if user presses top right button

  bluetooth_loop();
}


/*==================================FUNCITON DEFINITIONS==========================================*/

void updateTime(uint8_t * b) {
  int y, M, d, k, m, s;
  char * next;
  y = strtol((char *)b, &next, 10);
  M = strtol(next, &next, 10);
  d = strtol(next, &next, 10);
  k = strtol(next, &next, 10);
  m = strtol(next, &next, 10);
  s = strtol(next, &next, 10);
#if defined (ARDUINO_ARCH_AVR)
  setTime(k, m, s, d, M, y);
#elif defined(ARDUINO_ARCH_SAMD)
  rtc.setTime(k, m, s);
  rtc.setDate(d, M, y - 2000);
#endif
}

int minutesMS(int input)
{
  return input * 60000;
}

int minutesLeftInHour()
{
  return 60 - rtc.getMinutes();
}

// Calculate the battery voltage
float getBattVoltage(void) {
  const int VBATTpin = A4;
  float VCC = getVCC();

  // Use resistor division and math to get the voltage
  float resistorDiv = 0.5;
  float ADCres = 1023.0;
  float battVoltageReading = analogRead(VBATTpin);
  battVoltageReading = analogRead(VBATTpin); // Throw out first value
  float battVoltage = VCC * battVoltageReading / ADCres / resistorDiv;

  return battVoltage;
}

// This function gets the battery VCC internally, you can checkout this link
// if you want to know more about how:
// http://atmel.force.com/support/articles/en_US/FAQ/ADC-example
float getVCC() {
  SYSCTRL->VREF.reg |= SYSCTRL_VREF_BGOUTEN;
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->SAMPCTRL.bit.SAMPLEN = 0x1;
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->INPUTCTRL.bit.MUXPOS = 0x19;         // Internal bandgap input
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->SWTRIG.bit.START = 1;  // Start conversion
  ADC->INTFLAG.bit.RESRDY = 1;  // Clear the Data Ready flag
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->SWTRIG.bit.START = 1;  // Start the conversion again to throw out first value
  while ( ADC->INTFLAG.bit.RESRDY == 0 );   // Waiting for conversion to complete
  uint32_t valueRead = ADC->RESULT.reg;
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  SYSCTRL->VREF.reg &= ~SYSCTRL_VREF_BGOUTEN;
  float vcc = (1.1 * 1023.0) / valueRead;
  return vcc;
}

float getBattPercent()
{
  float batteryLeft = max((getBattVoltage() - 3.00), 0);
  return min((batteryLeft * 83.333333), 100); // hard upper limit of 100 as it often shows over 100 when charging
}

void checkPulse()
{
    if (pulseSensor.update()) {
      if (pulseSensor.pulseValid()) {
        beatAvg = pulseSensor.BPM();
      }
    }
}

int updatePedometer() {
 // if (millis() < sampleInterval + lastSample)return 0; we don't need to check this as it takes longer than sampleInterval to updatePulse anyway

  accel_sensor.read();//This function gets new data from the acccelerometer

  motionX = accel_sensor.X;
  motionY = accel_sensor.Y;
  motionZ = accel_sensor.Z;

}

void validateSD(String dataString, String displayString, bool firstSD)
{
  if (file.open(fileName, O_CREAT | O_RDWR | O_APPEND)) {
    logData(dataString, displayString);
  }
  file.close();
}

// Log a data record.
void logData(String dataString, String displayString) {
  uint16_t data[ANALOG_COUNT];

  // Read all channels to avoid SD write latency between readings.
  for (uint8_t i = 0; i < ANALOG_COUNT; i++) {
    data[i] = analogRead(i);
  }
 if (firstSD)
  {
    file.println(displayString);
    firstSD = false;
  }
  else if (firstSD == false) {
    file.println(dataString);
  }
}

void createString(String &displayString, String &dataString, bool firstSD, int currentHour, bool &validatedPreviously) {
  unsigned long epoch = rtc.getEpoch();
  
  int battery = getBattPercent();
  if (firstSD) // only the first line will look like this so that you know what data is in each column
  {
    displayString += "epochTime: ";
    displayString += String(epoch);
    displayString += ",";
    displayString += " pulse: ";
    displayString += String(beatAvg); // represents the average pulse recorded since the last time file was written to
    displayString += ",";
    
    Wireling.selectPort(pulseSensorPort);
    displayString += " X axis Position: ";
    displayString += String(motionX);
    displayString += ",";
    displayString += " Y axis Position: ";
    displayString += String(motionY);
    displayString += ",";    
    displayString += " Z axis Position ";
    displayString += String(motionZ);
    displayString += ",";
    Wireling.selectPort(accelSensorPort);
    displayString += " Stress: ";
    displayString += String(stressDetected);
  }
  else
  {
    dataString += String(epoch);
    dataString += ",";
    dataString += String(beatAvg);
    dataString += ",";
    
    Wireling.selectPort(pulseSensorPort);
    Wireling.selectPort(accelSensorPort);
    dataString += String(motionX);
    dataString += ",";
    dataString += String(motionY);
    dataString += ",";    
    dataString += String(motionZ);   
    dataString += ",";
    dataString += String(stressDetected);
  }
}

void resetHeartData()
{
  for (int i = 0; i < 2880; ++i)
  {
    heartData[i] = 0;
  }
}

void buzzLRA()
{
  Wireling.selectPort(lraSensorPort);
  
  // Set the effect to play
  drv.setWaveform(0, 17);      // Set effect 17
  drv.setWaveform(1, 0);       // End waveform

  // Play the effect
  drv.go();

  delay(500);
}

void checkButtons(unsigned long &screenClearTime)
{
  if(display.getButtons(TSButtonUpperLeft) || display.getButtons(TSButtonLowerLeft) || display.getButtons(TSButtonLowerRight))
  {
  
    int battery = getBattPercent();
    
    if(rtc.getSeconds() == 0 && millis()-screenClearTime > 1000){
      display.clearScreen();
      screenClearTime = millis();
    }
    
    display.on();
    display.setCursor(0,0);
    display.print(rtc.getMonth());
    display.print("/");
    display.print(rtc.getDay());
    display.print("/");
    display.print(rtc.getYear());
    display.print(" ");
    display.print(rtc.getHours());
    display.print(":");
    display.print(rtc.getMinutes());
    display.print(":");
    display.println(rtc.getSeconds());
    display.setCursor(0,10);
    display.print("Stress Detected: ");
    display.println(stressDetected);
    display.setCursor(0,20);
    display.print("Movement Y: ");
    display.println(motionY);
    display.setCursor(0,30);
    display.print("Movement Z: ");
    display.println(motionZ);
    display.setCursor(0,40);
    display.print("Heart Rate: ");
    display.println(beatAvg);    
    display.setCursor(0,50);
    display.print("Battery %: ");
    display.println(battery);
  }
  else
  {
    display.off();
  }
}

void stressDetectedButton(unsigned long &screenClearTime)
{
  if(display.getButtons(TSButtonUpperRight))
  {
  
    stressDetected = true;
  }
  else
  {
    display.off();
  }
}

void intialize_bluetooth(){
  // BLE  setup routine to be called in the setup section
  SerialMonitorInterface.begin(9600);
  while(!SerialMonitorInterface);
  BLEsetup();

}


void bluetooth_loop() {

  aci_loop();//Process any ACI commands or events from the NRF8001- main BLE handler, must run often. Keep main loop short.
  delay(10);//should catch input
  uint8_t sendBuffer[21] = {'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9', '\0'};
  uint8_t sendLength = 20;

  lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)sendBuffer, sendLength);
}

void initialize_sd_card(){
  // Check for SD card. If not initialized, terminate to infinite loop
  if (!SD.begin())
  {
    delay(5000);
    while (1);
  }
}

void intialize_lrasensor(){
  // Initialize lrasensor
  if (lraSensorPort) {
    drv.begin();
    drv.selectLibrary(1);
    drv.setMode(DRV2605_MODE_INTTRIG);
    drv.useLRA();
  }
}

void initialize_accelerometer(){
  // Initialize accelerometer
  if (accelSensorPort) {
    // Set the cursor to the following coordinates before it prints "BMA250 Test"
    Wireling.selectPort(accelSensorPort);
    accel_sensor.begin(BMA250_range_4g, BMA250_update_time_16ms); // Sets up the BMA250 accel_sensorerometer
  }
}

void initialize_pulse_sensor(){
  // Initialize pulseoximeter
  if (pulseSensorPort)
  {
    Wireling.selectPort(pulseSensorPort);
    pulseSensor.begin(); //Configure sensor with default settings
  }

}

void initialize_rtc(){
  //initialize RTC
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);//h,m,s
  rtc.setDate(day, month, year);//d,m,y
  //unsure how getEpoch is being displayed on excel file, but it is important in settting the date and time
  unsigned long tempEpoch = rtc.getEpoch();
  int tempHour = rtc.getHours();
  int tempMinute = rtc.getMinutes();
  
  rtc.setEpoch(tempEpoch); // reset back to current time

}

void initialize_display(){
  // Setup used to initialize the TinyScreen's appearance GUI.
  display.begin();
  display.setBrightness(15);
  display.setFlip(true);
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_White, background);
}

void initialize_wireling(){
  // Initialized wire and wireling classes for the sensors
  delay(5000); // replaces the above
  Wire.begin();
  Wireling.begin();
}