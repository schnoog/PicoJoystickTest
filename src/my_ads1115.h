#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
unsigned long LastTime = 0;

int chan = 0;
int an1 = 0;
int an2 = 0;
int an3 = 0;
int an0 = 0;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");

  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  ads.setGain(GAIN_ONE);
  // Start the first conversion.
  chan=0;
  ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_0, /*continuous=*/false);
}


void loop(void)
{
  // If we don't have new data, skip this iteration.
  if (ads.conversionComplete()) {
   
  
  unsigned long tdiff = micros()- LastTime;
  LastTime = micros();

  int16_t results = ads.getLastConversionResults();

  Serial.print("Success Looptime:"); Serial.print(tdiff);
  
  //Serial.print(" Differential: "); Serial.print(results); Serial.print("("); Serial.print(ads.computeVolts(results)); Serial.println("mV)");

  // Start another conversion.
  
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

  Serial.print(" Chan 3 / 2 / 1 / 0 ");
  Serial.print(an3);Serial.print(" / ");
  Serial.print(an2);Serial.print(" / ");
  Serial.print(an1);Serial.print(" / ");
  Serial.println(an0);

  }

  
  
  
  //Serial.println(results);

  //delay(1000);
}