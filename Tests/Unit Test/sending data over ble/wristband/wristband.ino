//-------------------------------------------------------------------------------
//  TinyCircuits ST BLE TinyShield UART Example Sketch
//  Last Updated 2 March 2016
//
//  This demo sets up the BlueNRG-MS chipset of the ST BLE module for compatiblity 
//  with Nordic's virtual UART connection, and can pass data between the Arduino
//  serial monitor and Nordic nRF UART V2.0 app or another compatible BLE
//  terminal. This example is written specifically to be fairly code compatible
//  with the Nordic NRF8001 example, with a replacement UART.ino file with
//  'aci_loop' and 'BLEsetup' functions to allow easy replacement. 
//
//  Written by Ben Rose, TinyCircuits http://tinycircuits.com
//
//-------------------------------------------------------------------------------

#include <Wire.h>
#include <TinyScreen.h>
#include <SPI.h>
#include <STBLE.h>


//Debug output adds extra flash and memory requirements!
#ifndef BLE_DEBUG
#define BLE_DEBUG true
#endif

//#if defined (ARDUINO_ARCH_AVR)
//#define SerialMonitorInterface Serial
//#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
//#endif

TinyScreen display = TinyScreen(TinyScreenPlus);

//default
uint8_t ble_rx_buffer[21];
uint8_t ble_rx_buffer_len = 0;
uint8_t ble_connection_state = false;
#define PIPE_UART_OVER_BTLE_UART_TX_TX 0

//Declare arrays and matrix to store data
uint8_t ble_x_buffer[21];
uint8_t ble_x_len = 0;
uint8_t ble_y_buffer[21];
uint8_t ble_y_len = 0;
uint8_t ble_z_buffer[21];
uint8_t ble_z_len = 0;
uint8_t ble_h_buffer[21];
uint8_t ble_h_len = 0;
uint8_t ary[3][4];


//initialise OLED, serial monitor, and ble
void setup() {
  display.begin();
  SerialMonitorInterface.begin(9600);
  //while (!SerialMonitorInterface); //This line will block until a serial monitor is opened with TinyScreen+!
  BLEsetup();
}

//main
void loop() {
  aci_loop();//Process any ACI commands or events from the NRF8001- main BLE handler, must run often. Keep main loop short.

  uint8_t data[1] = {'1'};
  lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)data, 1);
  delay(1000);

// /*obtain x-axis data and store it as a string
//  * 
//  * code here
//  * 
//  */
// String x = "11";  //test string
// //create array for x with first character 'x' to indicate that the numerical data following 'x' pertains to x-axis 
//   ble_x_len = x.length()+1;
//   for (int i = 1; i <= ble_x_len; i++) {
//     ble_x_buffer[0] = 'x';
//     ble_x_buffer[i] = x[i-1];
//   }
//   ble_x_len += 1;

// /*obtain y-axis data and store it as a string
//  * 
//  * code here
//  * 
//  */
//     String y = "22";  //test string
// //create array for y with first character 'y' to indicate that the numerical data following 'y' pertains to y-axis 
//     ble_y_len = y.length()+1;
//   for (int i = 1; i <= ble_y_len; i++) {
//     ble_y_buffer[0] = 'y';
//     ble_y_buffer[i] = y[i-1];
//   }
//   ble_y_len += 1;

// /*obtain z-axis data and store it as a string
//  * 
//  * code here
//  * 
//  */
//   String z = "33";  //test string
//   //create array for z with first character 'z' to indicate that the numerical data following 'z' pertains to z-axis 
//     ble_z_len = z.length()+1;
//   for (int i = 1; i <= ble_z_len; i++) {
//     ble_z_buffer[0] = 'z';
//     ble_z_buffer[i] = z[i-1];
//   }
//   ble_z_len += 1;

//   /*obtain hear rate data and store it as a string
//  * 
//  * code here
//  * 
//  */
//   String h = "44"; //test string
//     //create array for heart rate with first character 'h' to indicate that the numerical data following 'h' pertains to heart rate 
//     ble_h_len = h.length()+1;
//   for (int i = 1; i <= ble_h_len; i++) {
//     ble_h_buffer[0] = 'h';
//     ble_h_buffer[i] = h[i-1];
//   }
//   ble_h_len += 1;

//   //place accelerometer x,y, and z arrays in matrix
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (i==0){
//         ary[i][j] = ble_x_buffer[j];
//       }

//       if (i==1){
//         ary[i][j] = ble_y_buffer[j];
//       }

//       if (i==2) {
//         ary[i][j] = ble_z_buffer[j];
//       }

//       if (i==3) {
//         ary[i][j] = ble_h_buffer[j];
//       }
//     }
//   }

  
//   //default
//   if (ble_rx_buffer_len) {//Check if data is available
//     SerialMonitorInterface.print(ble_rx_buffer_len);
//     SerialMonitorInterface.print(" : ");
//     SerialMonitorInterface.println((char*)ble_rx_buffer);
//     ble_rx_buffer_len = 0;//clear afer reading
//   }
//   if (SerialMonitorInterface.available()) {//Check if serial input is available to send
//     delay(10);//should catch input
//     uint8_t sendBuffer[21];
//     uint8_t sendLength = 0;
//     while (SerialMonitorInterface.available() && sendLength < 19) {
//       sendBuffer[sendLength] = SerialMonitorInterface.read();
//       sendLength++;
//     }
//     if (SerialMonitorInterface.available()) {
//       SerialMonitorInterface.print(F("Input truncated, dropped: "));
//       if (SerialMonitorInterface.available()) {
//         SerialMonitorInterface.write(SerialMonitorInterface.read());
//       }
//     }
//     sendBuffer[sendLength] = '\0'; //Terminate string
//     sendLength++;
//     if (!lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)sendBuffer, sendLength))
//     {
//       SerialMonitorInterface.println(F("TX dropped!"));
//     }
//   }



// //upon meeting a condition, send accelerometer matrix and heart rate array over BLE to hm-10
// if(display.getButtons() == TSButtonUpperLeft){
//     lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)ary, ble_x_len + ble_y_len + ble_z_len);
//     delay(1000);//only for testing, remove line
//     lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)ble_h_buffer, ble_h_len);
//     delay(1000);//only for testing, remove line
//   }

// //wait for button release, only for testing. remove line
//     while(display.getButtons() == TSButtonUpperLeft){}
}