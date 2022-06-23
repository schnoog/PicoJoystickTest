#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#define IO_LOGGING_DEBUG

#include <IoAbstraction.h>
#include <IoLogging.h>
#include <TaskManagerIO.h>
#include <IoAbstractionWire.h>

#include <PicoGamepad.h>

//where the final states will be saves
int buttonState[16]  = {0, 0, 0, 0 , 0 , 0 , 0 , 0, 0 , 0, 0, 0, 0, 0, 0, 0};
int buttonPins[16]  = {0, 1, 2 , 3 , 4 , 5 , 6 , 7, 8 , 9, 10, 11, 12, 13, 14, 15};
int manResetPins[] = { 0 , 1};
// 0 & 1 --> rotary + / rotary -
int an1 = 0;
int an2 = 0;
int an3 = 0;
int an0 = 0;

 
//ini ads
#include <myjoy_ads.h>
//ini mcp
#include <myjoy_mcp.h>
//ini gamepad
//#include <myjoy_gamepad.h>

//ini debug output
#include <myjoy_out.h>



void setup(void)
{
      Serial.begin(9600);
      Serial.println("Hello!");
      ads_setup();
      taskManager.scheduleFixedRate(10, ads_loop);
      mcp_setup();

}

void loop(void)
{
      taskManager.runLoop();
      SerialOut();
      GamepadOut();
}