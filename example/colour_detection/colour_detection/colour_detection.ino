#include <Dezibot.h>

#include "Wire.h"
#include "veml6040.h"

Dezibot dezibot = Dezibot();

VEML6040 RGBWSensor;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");

  if(!RGBWSensor.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1){}
  }
  RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
	
  delay(1500);
  Serial.println("CCT: Correlated color temperature in \260K");
  Serial.println("AL: Ambient light in lux");
  delay(1500);
}

void loop() {
  printValue(RGBWSensor.getRed(), "R");
  printValue(RGBWSensor.getGreen(), "G");
  printValue(RGBWSensor.getBlue(), "B");
  printValue(RGBWSensor.getWhite(), "W");
  Serial.print(" CCT: ");
  Serial.print(RGBWSensor.getCCT());  
  Serial.print(" AL: ");
  Serial.println(RGBWSensor.getAmbientLight()); 
  delay(400);

  Serial.println("");
  dezibot.display.clear();
}

void printValue(uint16_t color, char* prefix) {
  dezibot.display.print(prefix);
  dezibot.display.print(" ");
  dezibot.display.println(color);

  Serial.print(prefix);
  Serial.print(" ");
  Serial.println(color);
}
