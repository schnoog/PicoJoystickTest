
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
unsigned long LastTime = 0;
int chan = 0;




void ads_setup(){
    Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
    Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS.");
        while (1);
    }
    ads.setGain(GAIN_ONE);
    // Start the first conversion.
    chan=0;
    ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_0, /*continuous=*/false);
}

void ads_loop(){
    if (ads.conversionComplete()) {
    int16_t results = ads.getLastConversionResults();

    
    switch(chan){
    case 1:
            ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_2, /*continuous=*/false);
            chan = 2;
            an1 = results;
            break;
    case 0:
            ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_1, /*continuous=*/false);
            chan = 1;
            an0 = results;
            break;
    case 3:
            ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_0, /*continuous=*/false); 
            chan = 0;
            an3 = results;
            break;
    case 2:
            ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_3, /*continuous=*/false); 
            chan = 3;
            an2 = results;

            break;
    default:
            break;
    }
  }
}