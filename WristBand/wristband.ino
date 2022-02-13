#include <SPI.h>
#include <MAX30101.h> // used to interface with the pulse oximetry sensor
#include "BMA250.h" // Used to interface with the acceleromter Wireling
#include <SdFat.h> // enables data to be logged to an sd card
#include <TinyScreen.h> // This library is used to print sensor values to a TinyScreen
#include <RTCZero.h>
#include <Wireling.h>
#include "Adafruit_DRV2605.h" // used to interface with the LRA Wireling

// date time information during compilation
#define HOURS 10
#define MINUTES 10
#define SEC 10
#define DAY 10
#define MONTH 10
#define YEAR 2022




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
void initializeRTC(uint8_t hours, uint8_t minutes, uint8_t seconds, uint_t day, uint8_t month, uint8_t year);

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

//RTC initialization
RTCZero rtc;


void setup(){
  SerialUSB.begin(9600);
  delay(5000); // replaces the above
  Wire.begin();
  Wireling.begin();

  initializeSDCard();
  initializeSensors(port_arr);
  initializeRTC(uint8_t HOURS, uint8_t MINUTES, uint8_t SECONDS, uint_t DAY, uint8_t MONTH, uint8_t YEAR);
  initializeDisplay();

  //timing setup
  rtc.begin(); // timing
}

void loop(){

}


// ================== FUNCTION DEFINITIONS ===================
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

void initializeRTC(uint8_t hours, uint8_t minutes, uint8_t seconds, uint_t day, uint8_t month, uint8_t year){
  /*Set the start time as of when the program is compiled.*/
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);//h,m,s
  rtc.setDate(day, month, year);//d,m,y
  unsigned long tempEpoch = rtc.getEpoch();
  int tempHour = rtc.getHours();
  int tempMinute = rtc.getMinutes();
  
  rtc.setEpoch(tempEpoch); // reset back to current time
}


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

//NEED
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

//NEED
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
        //NOT NEEDED
		//saturatedOxygen = pulseSensor.oxygen();
      }
    }
}


//NEED
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

void createString(String &displayString, String &dataString, bool firstSD, int currentHour, bool &validatedPreviously, unsigned long &validationEpoch) {
  int total = getTotalSteps();
  unsigned long epoch = rtc.getEpoch();
  
  /* //DONT NEED
  //int percent = percentOfDailyStepGoal(total); */
  
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
	
    /* //NOT NEEDED
	//displayString += String(saturatedOxygen); */
    
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
	
    /* //DONT NEED
	//int percent = percentOfDailyStepGoal(total);
 */    int battery = getBattPercent();
    
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
	  
	//CHECK FOR OTHER OXYGEN RELATED LINES
    //display.print("Oxygen: ");
    //NOT NEEDED
	//display.println(saturatedOxygen);
    display.setCursor(0,50);
    display.print("Battery %: ");
    display.println(battery);
  }
  else
  {
    display.off();
  }
}
