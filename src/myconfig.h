// pico pins-connection
int InterPin1 = 16;
int InterPin2 = 17;
int InterPin3 = 18;
int InterPin4 = 19;
int InterPin5 = 20;
int InterPin6 = 21;


int ThrottleMinPos = 3300; // value goes above = 3300 ---> PowerOff Switch  // value goes below 3300  ---> PowerOn



int AnalogThrottlePin = 26; // A0


//where the final states will be saves
int buttonState[18]  = {0, 0, 0, 0 , 0 , 0 , 0 , 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 16 & 17 -> power on, poweroff
int buttonPins[16]  = {0, 1, 2 , 3 , 4 , 5 , 6 , 7, 8 , 9, 10, 11, 12, 13, 14, 15};
int manResetPins[] = { 0 , 1};