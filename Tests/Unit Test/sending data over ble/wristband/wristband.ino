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


}