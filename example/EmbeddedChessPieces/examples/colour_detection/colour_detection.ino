/**
 * @file colour_detection.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to determine if Dezibot is on white or black surface
 * @version 0.1
 * @date 2024-10-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

Dezibot dezibot = Dezibot();
ECPColorDetection ecpColorDetection(dezibot);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");

  bool hasStartedSuccessfully = dezibot.colorSensor.begin();
  if(!hasStartedSuccessfully) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1) {}
  }
  delay(3000);
  
  ecpColorDetection.turnOnColorCorrectionLight();
}

void loop() {
  double ambient = dezibot.colorSensor.getNormalizedAmbientValue();

  double red = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::RED, ambient);
  double green = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::GREEN, ambient);
  double blue = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::BLUE, ambient);
  double white = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::WHITE, ambient);
  // double cct = dezibot.colorSensor.getCCT();

  double brightness = dezibot.colorSensor.calculateBrightness(red, green, blue);
  bool isWhite = ecpColorDetection.isWhiteField();

  Serial.println("");
  dezibot.display.clear();

  printValue(red, "R");
  printValue(green, "G");
  printValue(blue, "B");
  printValue(white, "W");

  // printValue(cct, "C");
  printValue(ambient, "A");
  printValue(brightness, "H");
  printIsWhiteField(isWhite);

  delay(500);
}

/**
 * @brief Print passed color value to dezibot display and serial monitor.
 * 
 * For example, `printValue(100, "R")` will result in `R 100`.
 * 
 * @param colorValue value of color to print
 * @param prefix prefix of color value to print, e.g. "R" for red
 */
void printValue(double colorValue, char* prefix) {
  dezibot.display.print(prefix);
  dezibot.display.print(" ");
  dezibot.display.println(String(colorValue, 4));

  Serial.print(prefix);
  Serial.print(" ");
  Serial.println(colorValue);
}

/**
 * @brief Print formatted info for isWhiteField.
 * 
 * \code{.cpp}
 * printIsWhiteField(true)
 * // "F W"
 * 
 * printIsWhiteField(false)
 * \endcode
 * ```
 * 
 * @param isWhiteField true if is white, false otherwise
 */
void printIsWhiteField(bool isWhiteField) {
  dezibot.display.print("F ");
  Serial.print("F ");
  String field = isWhiteField ? "W" : "B";
  dezibot.display.println(field);
  Serial.println(field);
}
