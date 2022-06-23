
PicoGamepad gamepad;

int AOUTCNT=0;


int ACutOffMap(int GetVal){
        int workval = GetVal;
        int val;
        if(GetVal < 1) workval =  0;
        if(GetVal > 25000) workval =  25000;
        val = map(workval, 0, 25000, -32767, 32767);
        return val;
}



void GamepadOut(){
  // Send value to HID object
    gamepad.SetX(ACutOffMap(an0));
    gamepad.SetY(ACutOffMap(an1));
    gamepad.SetS0(ACutOffMap(an2));
    gamepad.SetThrottle(ACutOffMap(an3));

  
  
//  gamepad.SetZ(val);
//  gamepad.SetRx(val);
//  gamepad.SetRy(val);
//  gamepad.SetRz(val);
//  gamepad.SetS0(val);
//  gamepad.SetS1(val);

  // Set button 0 of 128 by reading button on digital pin 28
  
    for (int i = 0 ; i < (sizeof(buttonPins)/4); i++) {
            gamepad.SetButton(i, buttonState[i]);
    }

    for (int i = 0 ; i < (sizeof(manResetPins)/4); i++) {
        buttonState[manResetPins[i]] = 0;
    }
  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER 
  // gamepad.SetHat(0, 8);


  // Send all inputs via HID 
  // Nothing is send to your computer until this is called.
  gamepad.send_update();


}



void SerialOut(){

    AOUTCNT++;
    if(AOUTCNT == 19){
        AOUTCNT = 0;
        Serial.println("0 / 1 / 2 / 3 / 4 / 5 / 6 / 7 / 8 / 9 / 10 / 11 / 12 / 13 / 14 / 15 / A3   / A2   / A1   / A0");
    }

    
    for (int i = 0 ; i < (sizeof(buttonState)/4); i++) {
        Serial.print( buttonState[i] );
        Serial.print(" / ");

    }

//    for (int i = 0 ; i < (sizeof(manResetPins)/4); i++) {
//        buttonState[manResetPins[i]] = 0;
//    }

        Serial.print(an3);Serial.print(" / ");
        Serial.print(an2);Serial.print(" / ");
        Serial.print(an1);Serial.print(" / ");
        Serial.println(an0);







}