#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>

#define IO_LOGGING_DEBUG

#include <IoAbstraction.h>
#include <IoLogging.h>
#include <TaskManagerIO.h>
#include <IoAbstractionWire.h>


const int encoderA = 0;
const int encoderB = 1;
const int attachedInterruptPin = 20;
const int mbutton1 = 2;
const int mbutton2 = 7;
const int mbutton3 = 15;

IoAbstractionRef io23017;

void onKeyPressed(pinid_t key, bool held) {
    serdebugF3("key pressed", key, held);
    //ioDeviceDigitalWrite(io23017, ledA, HIGH);
    //ioDeviceDigitalWriteS(io23017, ledB, HIGH);
}

void onKeyReleased(pinid_t key, bool held) {
    serdebugF3("key released", key, held);
    //ioDeviceDigitalWrite(io23017, ledA, LOW);
    //ioDeviceDigitalWriteS(io23017, ledB, LOW);
}

void onEncoderChange(int encoderValue) {
    serdebugF2("encoder = ", encoderValue);
    //ioDeviceDigitalWrite(io23017, ledA, encoderValue < 0);
    //ioDeviceDigitalWriteS(io23017, ledB, encoderValue > 0);
}




void setup(void)
{
    Wire.begin();
    Serial.begin(9600);
    io23017 = ioFrom23017(0x20, ACTIVE_LOW_OPEN, attachedInterruptPin);

    serdebugF("Starting example");
    //switches.init(io23017,SWITCHES_POLL_EVERYTHING,true);
    switches.init(io23017, SWITCHES_NO_POLLING, true);
    switches.addSwitch(mbutton1, onKeyPressed, 20);
    switches.onRelease(mbutton1, onKeyReleased);
    switches.addSwitch(mbutton2, onKeyPressed, 20);
    switches.onRelease(mbutton2, onKeyReleased);
    switches.addSwitch(mbutton3, onKeyPressed, 20);
    switches.onRelease(mbutton3, onKeyReleased);
    setupRotaryEncoderWithInterrupt(encoderA, encoderB, onEncoderChange,HWACCEL_REGULAR,QUARTER_CYCLE);
}


void loop(void)
{
taskManager.runLoop();
}