#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#define IO_LOGGING_DEBUG

#include <IoAbstraction.h>
#include <IoLogging.h>
#include <AnalogDeviceAbstraction.h>
#include <TaskManagerIO.h>
#include <IoAbstractionWire.h>
#include <PicoGamepad.h>
#include <myconfig.h>






// 0 & 1 --> rotary + / rotary -
int an1 = 0;
int an2 = 0;
int an3 = 0;
int an0 = 0;
int ThrottleRawVal = 0;
int ThrottleRawOld = ThrottleMinPos;
int ThrottleVal = 0;

#include <myi2c.h> 

//ini ads
#include <myjoy_ads.h>
//ini mcp
#include <myjoy_mcp.h>
//ini gamepad
//#include <myjoy_gamepad.h>

//ini debug output
#include <myjoy_out.h>
AnalogDevice* analog = internalAnalogIo();


void setup(void)
{
      Serial.begin(9600);
      Serial.println("Hello!");
      setActiveI2C();
      ads_setup();
      analog->initPin(AnalogThrottlePin, DIR_IN);
      taskManager.scheduleFixedRate(10, ads_loop);
      mcp_setup();

}

void loop(void)
{
      ThrottleRawVal = analog->getCurrentValue(AnalogThrottlePin);
      int TVAL = ThrottleRawVal;
      if(TVAL < 80) TVAL = 80;
      if(TVAL > ThrottleMinPos) TVAL = ThrottleMinPos;
      boolean IsStart = false;
      boolean IsStop = false;
      if(ThrottleRawOld >= ThrottleMinPos){
            if(ThrottleRawVal <= ThrottleMinPos) IsStart = true;
      }

      if(ThrottleRawOld <= ThrottleMinPos){
            if(ThrottleRawVal >= ThrottleMinPos) IsStop = true;
      }
      buttonState[16] = 0;
      buttonState[17] = 0;
      if(IsStart) buttonState[16] = 1;
      if(IsStop) buttonState[17] = 1;
      ThrottleRawOld = ThrottleRawVal;




      ThrottleVal = map(TVAL,80,ThrottleMinPos,-32767,32767);
      ThrottleVal = ThrottleVal * -1;
      taskManager.runLoop();
      SerialOut();
      GamepadOut();
}