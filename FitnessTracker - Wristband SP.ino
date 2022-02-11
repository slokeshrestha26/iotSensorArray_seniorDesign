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
//NEED ALL LIBRARIES
#include <SPI.h>
#include <TinyScreen.h> // This library is used to print sensor values to a TinyScreen
#include "BMA250.h" // Used to interface with the acceleromter Wireling, which is used to track your steps
#include <Wire.h>
#include <Wireling.h>
#include "Adafruit_DRV2605.h" // used to interface with the LRA Wireling
#include <SdFat.h> // enables data to be logged to an sd card
#include <RTCZero.h>  // enables date and time to be recorded with each sensor reading
#include <MAX30101.h> // used to interface with the pulse oximetry sensor
#include "sleepStages.h" // contains examples of ideal sleep chronologies, which are used as part of the sleep scoring algorithm
#include <SD.h> // contains what's needed to find and access SD card.

Adafruit_DRV2605 drv; // lra sensor object
MAX30101 pulseSensor = MAX30101(); // pulseOx sensor object
BMA250 accel_sensor; // accelerometer sensor object

// SD card variables
#define FILE_BASE_NAME "worktst.csv" // Log file base name.  Must be 13 characters or less.
char fileName[13] = FILE_BASE_NAME;
SdFat SD; // File system object.
SdFile file; // Log file.
SdFile quartiles; // keeps track of your historical heart rate during sleep, which is used in the sleep quality calculation

const uint8_t ANALOG_COUNT = 4;

const int chipSelect = 10;

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

#include <RTCZero.h>
RTCZero rtc;

// heart rate variables
const byte RATE_SIZE = DATA_INTERVAL * 100; // Based on the data interval. this could take a lot of memory
byte rates[RATE_SIZE]; //heartDataay of heart rates
int beatAvg = 0; // represents the average heart rate over the DATA_INTERVAL

int stepArr[4] = {};

void initStepTimestamps();
bool validatePorts();
int updatePedometer();
void createString(String &, String &, bool , int , bool &);
void validateSD(String , String , bool );
void buzzLRA();
void checkButtons(unsigned long &screenClearTime);
float normalizedCrossCorrelation(const byte First[], byte Second[], float whichArray);

void setup(void)
{
  SerialUSB.begin(115200);
  delay(5000); // replaces the above
  initStepTimestamps();
  Wire.begin();
  Wireling.begin();

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

  rtc.begin();
  rtc.setTime(hours, minutes, seconds);//h,m,s
  rtc.setDate(day, month, year);//d,m,y
  unsigned long tempEpoch = rtc.getEpoch();
  int tempHour = rtc.getHours();
  int tempMinute = rtc.getMinutes();
	
  rtc.setEpoch(tempEpoch); // reset back to current time
  //Dont need EPOCH DIff
	
  // This is the setup used to initialize the TinyScreen's appearance GUI this is important.
  display.begin();
  display.setBrightness(15);
  display.setFlip(true);
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_White, background);
}

//Main function here.
void loop() {
  String displayString = ""; // written once in the logfile to provide column headings along with the data
  String dataString = ""; // written to the logfile every data interval seconds. does not contain headings, just csv data only. see createstring for more details
  static int emptyIntsCounter = 0;
  static unsigned long screenClearTime = millis();
  static int currentHour = rtc.getHours(); // performance optimization
  static bool validatedPreviously = false; // avoids the need to constantly validate whether it is past bedtime or not by store the fact within this variable.
  
  // NEED TO CHECK AND SEE IF THESE ARE STILL PRESENT AFTER REMOVING THE OBVIOUS	
  // note that the many areas of the sketch are not executed except at night when calculating or recording sleep quality.
  static unsigned long batt = millis(); // used to check the battery voltage and run some other code every data reporting inverval, default 30 seconds
  static unsigned long goalTimer = millis(); // used to check if you are meeting your daily goals
  static int heartIndex = 0;
  // these variables are used to keep track of how many steps were taken in recent minutes
  static unsigned long one = millis();
  static unsigned long two = millis();
  static unsigned long five = millis();
  static unsigned long fifteen = millis();
  static unsigned long oneMinute = millis();
  
  Wireling.selectPort(pulseSensorPort);  
  checkPulse();
  
  Wireling.selectPort(accelSensorPort);
  updatePedometer();
  if (millis() - batt > FAST_DATA_INTERVAL) // record battery voltage when needed
  {
    createString(displayString, dataString, firstSD, currentHour, validatedPreviously); //create strings from recent data
    validateSD(dataString, displayString, firstSD); // write the strings to the SD card after validating the connection to the SD card is intact
      Wireling.selectPort(pulseSensorPort);
      if(pulseSensor.update()){
        if (pulseSensor.pulseValid()) {
          beatAvg = pulseSensor.BPM();
          heartData[heartIndex] = pulseSensor.BPM();
          ++heartIndex;
        }
      }
    batt = millis();
  }

  if (millis() - oneMinute > 60000)
  {
	
	oneMinute = millis();
  
  }

  checkButtons(screenClearTime); // will activate display if user presses any button on the TS+
}

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

int getStepTrigger()
{
  return STEP_TRIGGER;
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
  if (DEBUG_MD) {
    SerialUSB.print("battery left: ");
    SerialUSB.println(min(batteryLeft * 83.333333, 100));
  }
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

void validateSD(String dataString, String displayString, bool firstSD)
{
  if (!file.open(fileName, O_CREAT | O_RDWR | O_APPEND)) {
    SerialUSB.println("File open error!");
  }
  else
  {
    // if the file is available, write to it:
    logData(dataString, displayString);
  }

  // Force data to SD and update the directory entry to avoid data loss.
  if (!file.sync() || file.getWriteError()) {
    SerialUSB.println("write error");
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
  if (DEBUG_MD) {
    SerialUSB.println("WRITING TO FILE!!");
  }
 if (firstSD)
  {
    file.println(displayString);
    firstSD = false;
  }
  else if (firstSD == false) {
    file.println(dataString);
  }
  if (DEBUG_MD) {
    SerialUSB.println("WRITING Complete!");
    SerialUSB.print("dataString: ");
    SerialUSB.println(dataString);
  }
}

void createString(String &displayString, String &dataString, bool firstSD, int currentHour, bool &validatedPreviously) {
  int total = getTotalSteps();
  unsigned long epoch = rtc.getEpoch();
  
  int battery = getBattPercent();
  if (firstSD) // only the first line will look like this so that you know what data is in each column
  {
    displayString += "epochTime: ";
    displayString += String(epoch);
    displayString += ",";
    displayString += " stepCount: ";
    displayString += String(total);
    displayString += ",";
    displayString += " stepPercent: ";
    displayString += String(percent);
    displayString += ",";
    displayString += " pulse: ";
    displayString += String(beatAvg); // represents the average pulse recorded since the last time file was written to
    displayString += ",";
    
    Wireling.selectPort(pulseSensorPort);
    displayString += " Oxygen Saturation: ";
    
    displayString += ",";
    Wireling.selectPort(accelSensorPort);
    displayString += " batt: ";
    displayString += String(battery);
  }
  else
  {
    dataString += String(epoch);
    dataString += ",";
    dataString += String(total);
    dataString += ",";
    dataString += String(percent);
    dataString += ",";
    dataString += String(beatAvg);
    dataString += ",";
    
    Wireling.selectPort(pulseSensorPort);
    
    dataString += ",";
    Wireling.selectPort(accelSensorPort);
    dataString += String(battery);
  }
}

String getFirst(int &emptyIntsCounter)
{
  //sorting - ASCENDING ORDER
  for (int i = 0; i < 2880; i++)
  {
    for (int j = i + 1; j < 2880; j++)
    {
      if (heartData[i] > heartData[j])
      {
        int temp  = heartData[i];
        heartData[i] = heartData[j];
        heartData[j] = temp;
      }
    }
  }

  for (int i = 0; i < 2880; ++i)
  {
    if (heartData[i] == 0)
    {
      ++emptyIntsCounter;
    }
  }
  return String(max(10, heartData[(int)((2880 - emptyIntsCounter) * 0.25) + emptyIntsCounter])); // after the array is sorted, we know the index of the first quartile after adjusting for unfilled array positions characterized by 0's
}

String getThird(int &emptyIntsCounter) // must be called immediatly after getFirst, otherwise the array will not be sorted
{
  int thirdQuartile = heartData[(int)((2880 - emptyIntsCounter) * 0.75) + emptyIntsCounter];
  resetHeartData(); // reset the array to 0's once we have calculated the quartile values to avoid old values being used in the next quartile calculation
  emptyIntsCounter = 0; // same reason as above
  return String(max(10, thirdQuartile));
}

void resetHeartData()
{
  for (int i = 0; i < 2880; ++i)
  {
    heartData[i] = 0;
  }
}

float normalizedCrossCorrelation(const byte First[], byte Second[], float whichArray) // takes into account the similarity between the values of two arrays and the order in which those values occur https://en.wikipedia.org/wiki/Cross-correlation
{
  float sum1 = 0;
  float temp = 0;
  float temp2 = 0;
  float sqsum1 = 0;
  float sqsum2 = 0;
  float Fm = 0;
  float Sm = 0;
  int size = sleepStageCounter;
  SerialUSB.print("size: ");
  SerialUSB.println(size);

  for (int i = 0; i < size; i++) {
    temp += First[i];
  }
  for (int i = 0; i < size; i++) {
    temp2 += Second[i];
  }

  Fm = temp / size;
  Sm = temp2 / size;

  for (int i = 0; i < size; i++) {
    sum1 += (First[i] - Fm) * (Second[i] - Sm);
    sqsum1 += pow((First[i] - Fm), 2);
    sqsum2 += pow((Second[i] - Sm), 2);
  }
  float result = (sum1 / (sqrt(sqsum1 * sqsum2)));
  SerialUSB.print("NCC Second & First : ");
  SerialUSB.println(result);
  if(isnan(result)) 
  {
    SerialUSB.println("error calcualting NCC!!");
    return 0.5;
  }
  return result;
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
  if(display.getButtons(TSButtonUpperLeft) || display.getButtons(TSButtonUpperRight) || display.getButtons(TSButtonLowerLeft) || display.getButtons(TSButtonLowerRight))
  {
    int total = getTotalSteps();
	
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
    display.print(rtc.getSeconds());
    display.setCursor(0,10);
    display.print("Steps: ");
    display.println(total);
    display.setCursor(0,20);
    display.print("Step %: "); 
    display.println(percent);
    display.setCursor(0,30);
    display.print("Heart Rate: ");
    display.println(beatAvg);
    display.setCursor(0,40);
	  
    display.setCursor(0,50);
    display.print("Battery %: ");
    display.println(battery);
  }
  else
  {
    display.off();
  }
}
