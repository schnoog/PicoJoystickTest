


const int encoderA = 0;
const int encoderB = 1;
const int attachedInterruptPin = 20;
const int mbutton1 = 2;
const int mbutton2 = 7;
const int mbutton3 = 15;




IoAbstractionRef io23017;


boolean arrayIncludeElement(int array[], int element) {
  for (int i = 0; i < (sizeof(array)/4); i++) {
    if (array[i] == element) {
      return true;
    }
  }
  return false;
}


void onKeyPressed(pinid_t key, bool held) {
    buttonState[key] = 1;
    //serdebugF3("key pressed", key, held);
    //ioDeviceDigitalWrite(io23017, ledA, HIGH);
    //ioDeviceDigitalWriteS(io23017, ledB, HIGH);
}

void onKeyReleased(pinid_t key, bool held) {
    if(!arrayIncludeElement(manResetPins,key)){
    buttonState[key] = 0;
    //serdebugF3("key released", key, held);
    }
}

void onEncoderChange(int encoderValue) {
    //serdebugF2("encoder = ", encoderValue);
    if(encoderValue == 1) {buttonState[0] = 1;}
    if(encoderValue == -1) {buttonState[1] = 1;}
}


void mcp_setup(){
    int Btn;
    io23017 = ioFrom23017(0x20, ACTIVE_LOW_OPEN, InterPin6);
    serdebugF("Starting example");
    switches.init(io23017, SWITCHES_NO_POLLING, true);
    for (int i = sizeof(manResetPins)/4 - 1 ; i < (sizeof(buttonPins)/4); i++) {
        Btn = buttonPins[i];
        switches.addSwitch(Btn, onKeyPressed, 20);
        switches.onRelease(Btn, onKeyReleased);
    }
    setupRotaryEncoderWithInterrupt(encoderA, encoderB, onEncoderChange,HWACCEL_REGULAR,QUARTER_CYCLE);
}