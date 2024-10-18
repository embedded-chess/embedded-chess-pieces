#include <Dezibot.h>

Dezibot dezibot = Dezibot();

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
}

void loop() {
  printValue(VEML_RED, "R");
  printValue(VEML_GREEN, "G");
  printValue(VEML_BLUE, "B");
  printValue(VEML_WHITE, "W");

  delay(500);
  Serial.println("");
  dezibot.display.clear();
}

void printValue(color color, char* prefix) {
  uint16_t colorValue = dezibot.colorDetection.getColorValue(color);

  dezibot.display.print(prefix);
  dezibot.display.print(" ");
  dezibot.display.println(colorValue);

  Serial.print(prefix);
  Serial.print(" ");
  Serial.println(colorValue);
}
