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

#define SerialMonitorInterface SerialUSB
#define PIPE_UART_OVER_BTLE_UART_TX_TX 0

// Data array size
#define DATA_ACC_LENGHT_PER_AXIS 780
#define DATA_HR_LENGTH 30
#define BLE_BUFF_SIZE 5

// global variable for inference mode flag
volatile uint8_t INFERENCE_MODE = 1; //flag for inference mode (default is 1)

// inference mode variables
uint8_t ble_rx_buffer[BLE_BUFF_SIZE];
uint8_t ble_rx_buffer_len = 0;
uint8_t ble_connection_state = false;

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

// used to store which sensors are connected and if so, what port they are connected to
int pulseSensorPort = 0;
int accelSensorPort = 3;

unsigned long loopStart = 0;

RTCZero rtc;

// heart rate variables
const byte RATE_SIZE = DATA_INTERVAL * 100; // Based on the data interval. this could take a lot of memory
byte rates[RATE_SIZE]; //heartDataay of heart rates
int beatAvg = 0; // represents the average heart rate over the DATA_INTERVAL

// acc variables
int motionX = 0; // x axis motion
int motionY = 0; // y axis motion
int motionZ = 0; // z axis motion

//count iterations since last heart rate storage
int hertzCount = 26;

//counts where we are in the heart array
int heartCounter = 0;

//shows a 0 if no stress detected and a 1 if stress is detected, Default is 0
int stressDetected = 0;

//block length data point saved when converted to character
uint8_t block_len = 5;

//The amount of data points for a minute for the axis
uint8_t data_length = DATA_ACC_LENGHT_PER_AXIS;

//multidimensional arrays to store all data for a minute
// Example of data [['x','-','1','2','3'], ['x','0',....]]

uint8_t x_array[DATA_ACC_LENGHT_PER_AXIS][BLE_BUFF_SIZE];
uint8_t y_array[DATA_ACC_LENGHT_PER_AXIS][BLE_BUFF_SIZE];
uint8_t z_array[DATA_ACC_LENGHT_PER_AXIS][BLE_BUFF_SIZE];
uint8_t h_array[DATA_HR_LENGTH][BLE_BUFF_SIZE];
uint8_t ble_buffer[BLE_BUFF_SIZE];

//arrays used to store the data collected for the single iteration
uint8_t x_index[5];
uint8_t y_index[5];
uint8_t z_index[5];
uint8_t h_index[5];

/*/*==================================Fuction prototype/*==================================*/
bool validatePorts();
int updatePedometer();
void checkButtons(unsigned long &screenClearTime);
void checkPulse();

void initialize_wireling();
void intialize_bluetooth();
void initialize_accelerometer();
void initialize_pulse_sensor();
void initialize_rtc();
void initialize_display();

void displayStress(unsigned long &);

void fillDataX(int);
void fillDataY(int);
void fillDataZ(int);
void fillDataH(int);

void send_data_ble();

/*==================================MAIN SETUP AND LOOP==========================================*/
void setup(void)
{
  intialize_bluetooth();
  initialize_accelerometer();
  initialize_pulse_sensor();
  initialize_rtc();
  initialize_display();
  initialize_wireling();
}


void loop() {
  static int emptyIntsCounter = 0;
  static unsigned long screenClearTime = millis();
  static int currentHour = rtc.getHours(); // performance optimization

  int heartIndex = 0;

  heartCounter = 0;

  for(int i=0; i<=DATA_ACC_LENGHT_PER_AXIS; i++){
    Wireling.selectPort(pulseSensorPort);  
    checkPulse();
    
    Wireling.selectPort(accelSensorPort);
    updatePedometer();
    if(pulseSensor.update()){
      if (pulseSensor.pulseValid()) {
        beatAvg = pulseSensor.BPM();
        heartData[heartIndex] = pulseSensor.BPM();
        ++heartIndex;
      }
    }
    
    checkButtons(screenClearTime); // will activate display if user presses any button except top right

    //Storing every iteration of data
    if(hertzCount > 26){
      fillDataH(beatAvg);
      hertzCount = 0;
      heartIndex++;
      for (int j = 0; j < block_len; j++) {
        h_array[heartCounter][j] = h_index[j];
      }
      heartCounter++;
    }
    else{
      hertzCount++;
    }

    fillDataX(motionX);
    fillDataY(motionY);
    fillDataZ(motionZ);

    //place data pulled from x,y,z, and h into their corresponding arrays
    for (int j = 0; j < block_len; j++) {
      x_array[i][j] = x_index[j];
      y_array[i][j] = y_index[j];
      z_array[i][j] = z_index[j];
    }    
  }

  //Send heartData, xData, yData, zData, & epochTime
  aci_loop();
  send_data_ble();
  //Checking to see if we have recieved a 1 from the bluetooth of the waistband, to detect if we have stress.
  // Now, since only thing that waistband sends the wristband is stress notification, only checking ble_rx_buffer is fine.
  if(ble_rx_buffer){
    displayStress(screenClearTime);
    ble_rx_buffer_len = 0;
  }

}


/*==================================FUNCITON DEFINITIONS==========================================*/

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

void resetHeartData()
{
  for (int i = 0; i < 2880; ++i)
  {
    heartData[i] = 0;
  }
}

void checkButtons(unsigned long &screenClearTime)
{
  if(display.getButtons(TSButtonUpperLeft))
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
    display.print("Movement X: ");
    display.println(motionX);
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
  }else
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

void send_data_ble(){
  for(int i = 0; i < DATA_ACC_LENGHT_PER_AXIS; i++){
    // copy the data to the ble_buffer
    for(int j = 0; j < BLE_BUFF_SIZE; j++){
      ble_buffer[j] = x_array[i][j];
    }
    bluetooth_loop();
    // copy the data to the ble_buffer
    for(int j = 0; j < BLE_BUFF_SIZE; j++){
      ble_buffer[j] = y_array[i][j];
    }
    bluetooth_loop();
    // copy the data to the ble_buffer
    for(int j = 0; j < BLE_BUFF_SIZE; j++){
      ble_buffer[j] = z_array[i][j];
    }
    bluetooth_loop();
    
    if(i < DATA_HR_LENGTH){
      // copy the data to the ble_buffer
      for(int j = 0; j < BLE_BUFF_SIZE; j++){
      ble_buffer[j] = h_array[i][j];
    }
      bluetooth_loop();
    }
  }
}

void bluetooth_loop() {
  /**/

  aci_loop();//Process any ACI commands or events from the NRF8001- main BLE handler, must run often. Keep main loop short.
  delay(10);//should catch input
  uint8_t sendLength = BLE_BUFF_SIZE;
  lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)ble_buffer, sendLength);
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

void displayStress(unsigned long &screenClearTime)
{ 
  int battery = getBattPercent();

  if(rtc.getSeconds() == 0 && millis()-screenClearTime > 1000){
    display.clearScreen();
    screenClearTime = millis();
  }
  
  display.on();
  display.setCursor(0,0);
  display.print("Stress Detected");
  display.setCursor(0,10);
  display.print("Please Breath: Inhale");
  delay(10000);
  display.setCursor(0,20);
  display.print("1");
  delay(10000);
  display.setCursor(0,30);
  display.print("2");
  delay(10000);
  display.setCursor(0,40);
  display.print("3: Exhale");
}

void fillDataX(int intData){
    x_index[0] = 'x';
    String x = "";
    if(intData < 0){
      int xN = intData * -1;
      x = String(xN);
      x_index[1] = '-';
      switch(x.length()){
        //adds 2 zeros infront of integer string
        case 1:
          x = "00" + x;
          break;
        //adds 1 zero infront of integer string
        case 2:
          x = "0" + x;
          break;
        default:
          break;
      }
    }
    else{
      x = String(intData);
      x_index[1] = '0';
      switch(x.length()){
        //adds 2 zeros infront of integer string
        case 1:
          x = "00" + x;
          break;
        //adds 1 zero infront of integer string
        case 2:
          x = "0" + x;
          break;
        default:
          break;
      }
    }

    for (int j = 2; j < block_len; j++) {
       x_index[j] = x[j-2];
    }

}

void fillDataY(int intData){
    y_index[0] = 'y';
    String y = "";
    if(intData < 0){
      int yN = intData * -1;
      y = String(yN);
      y_index[1] = '-';
      switch(y.length()){
        //adds 2 zeros infront of integer string
        case 1:
          y = "00" + y;
          break;
        //adds 1 zero infront of integer string
        case 2:
          y = "0" + y;
          break;
        default:
          break;
      }
    }
    else{
      y = String(intData);
      y_index[1] = '0';
      switch(y.length()){
        //adds 2 zeros infront of integer string
        case 1:
          y = "00" + y;
          break;
        //adds 1 zero infront of integer string
        case 2:
          y = "0" + y;
          break;
        default:
          break;
      }
    }

    for (int j = 2; j < block_len; j++) {
       y_index[j] = y[j-2];
    }

}

void fillDataZ(int intData){
    z_index[0] = 'z';
    String z = "";
    if(intData < 0){
      int zN = intData * -1;
      z = String(zN);
      z_index[1] = '-';
      switch(z.length()){
        //adds 2 zeros infront of integer string
        case 1:
          z = "00" + z;
          break;
        //adds 1 zero infront of integer string
        case 2:
          z = "0" + z;
          break;
        default:
          break;
      }
    }
    else{
      z = String(intData);
      z_index[1] = '0';
      switch(z.length()){
        //adds 2 zeros infront of integer string
        case 1:
          z = "00" + z;
          break;
        //adds 1 zero infront of integer string
        case 2:
          z = "0" + z;
          break;
        default:
          break;
      }
    }

    for (int j = 2; j < block_len; j++) {
       z_index[j] = z[j-2];
    }

}

void fillDataH(int intData){
    h_index[0] = 'h';
    String h = "";
    h = String(intData);
    h_index[1] = '0';
    switch(h.length()){
      //adds 2 zeros infront of integer string
      case 1:
        h = "00" + h;
        break;
      //adds 1 zero infront of integer string
      case 2:
        h = "0" + h;
        break;
      default:
        break;
    }

    for (int j = 2; j < block_len; j++) {
       h_index[j] = h[j-2];
    }

}
