
int AOUTCNT=0;

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

    for (int i = 0 ; i < (sizeof(manResetPins)/4); i++) {
        buttonState[manResetPins[i]] = 0;
    }

        Serial.print(an3);Serial.print(" / ");
        Serial.print(an2);Serial.print(" / ");
        Serial.print(an1);Serial.print(" / ");
        Serial.println(an0);







}