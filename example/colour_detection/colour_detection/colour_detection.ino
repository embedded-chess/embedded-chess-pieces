#include <Dezibot.h>

#include "Wire.h"
#include "veml6040.h"

Dezibot dezibot = Dezibot();

VEML6040 RGBWSensor;

const double MAX_COLOR_VALUE = 255.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");

  if(!RGBWSensor.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1) {}
  }
  RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  delay(3000);
}

void loop() {
  float ambient = (RGBWSensor.getAmbientLight() / 2061.0) * MAX_COLOR_VALUE;
  float red = min(255.0, ((RGBWSensor.getRed() * ambient) / 65535.0) * MAX_COLOR_VALUE);
  float green = min(255.0, ((RGBWSensor.getGreen() * ambient) / 65535.0) * MAX_COLOR_VALUE);
  float blue = min(255.0, ((RGBWSensor.getBlue() * ambient) / 65535.0) * MAX_COLOR_VALUE);
  float white = min(255.0, ((RGBWSensor.getWhite() * ambient) / 65535.0) * MAX_COLOR_VALUE);
  float brightness = min(255.0, 0.299 * red + 0.587 * green + 0.114 * blue);

  printValue(red, "R");
  printValue(green, "G");
  printValue(blue, "B");
  printValue(white, "W");

  printValue(RGBWSensor.getCCT() * 1.0, "C");           // Correlated color temperature in K
  printValue(ambient, "A");                                  // Ambient light in lux
  printValue(brightness, "H");
  // TODO: function to check if brightness < 100

  delay(400);
  Serial.println("");
  dezibot.display.clear();
}

void printValue(float colorValue, char* prefix) {
  dezibot.display.print(prefix);
  dezibot.display.print(" ");
  dezibot.display.println(String(colorValue, 4));

  Serial.print(prefix);
  Serial.print(" ");
  Serial.println(colorValue);
}
