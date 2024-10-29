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
#include <Wire.h>
#include <veml6040.h>

Dezibot dezibot = Dezibot();
VEML6040 rgbwSensor;
 
const double MAX_COLOR_VALUE = 255.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");

  if(!rgbwSensor.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1) {}
  }
  rgbwSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  delay(3000);
  turnOnColorCorrectionLight();
}

/**
 * @brief Turn on the LED on the bottom of the Dezibot.
 * 
 * The light should help the identification of the field color even in a dimly-lit room.
 */
void turnOnColorCorrectionLight() {
  uint32_t COLOR_CORRECTION_WHITE = dezibot.multiColorLight.color(43, 33, 35);
  dezibot.multiColorLight.setLed(BOTTOM,COLOR_CORRECTION_WHITE);
}

void loop() {
  double ambient = getNormalizedAmbientValue();

  double red = getNormalizedColorValue(VEML_RED, ambient);
  double green = getNormalizedColorValue(VEML_GREEN, ambient);
  double blue = getNormalizedColorValue(VEML_BLUE, ambient);
  double white = getNormalizedColorValue(VEML_WHITE, ambient);

  double brightness = calculateBrightness(red, green, blue);

  // Correlated color temperature in K
  double cct = rgbwSensor.getCCT() * 1.0;

  bool isWhite = isWhiteField(brightness);

  printValue(red, "R");
  printValue(green, "G");
  printValue(blue, "B");
  printValue(white, "W");

  // printValue(cct, "C");
  printValue(ambient, "A");
  printValue(brightness, "H");
  printIsWhiteField(isWhite);

  delay(500);
  Serial.println("");
  dezibot.display.clear();
}

/**
 * @brief Get normalized value of ambient light sensor on a scale from 0 to 255.
 * 
 * @return double normalized value
 */
double getNormalizedAmbientValue() {
  const double MAX_AMBIENT_VALUE = 2061.0;

  // ambient light in lux
  double ambient = rgbwSensor.getAmbientLight();
  double normalizedValue = ambient / MAX_AMBIENT_VALUE * MAX_COLOR_VALUE;
  return normalizedValue;
}

/**
 * @brief Get raw color value of RGBW sensor (**not** normalized!).
 *
 * Raw value is scaled on 16 bits.
 * For normalized value see \p getNormalizedColorValue.
 * 
 * @param color color which to get
 * @return double color value
 */
double getRawColorValue(color color) {
  switch (color) {
    case VEML_RED:
      return rgbwSensor.getRed();
    case VEML_GREEN:
      return rgbwSensor.getGreen();
    case VEML_BLUE:
      return rgbwSensor.getBlue();
    case VEML_WHITE:
      return rgbwSensor.getWhite();
  }
}

/**
 * @brief Get the normalized value of color sensor on a scale of 0 to 255 based
 *        on ambient lighting conditions.
 *
 * For \p ambientLightValue please use \p getNormalizedColorValue.
 * 
 * @param color color which to get value for
 * @param ambientLightValue **normalized** value of ambient light sensor
 * @return double normalized color value
 */
double getNormalizedColorValue(color color, double ambientLightValue) {
  const double MAX_SENSOR_VALUE = 65535.0;

  double colorValue = getRawColorValue(color);
  double normalizedValue = colorValue * ambientLightValue / MAX_SENSOR_VALUE * MAX_COLOR_VALUE;
  normalizedValue = min(MAX_COLOR_VALUE, normalizedValue);
  return normalizedValue;
}

/**
 * @brief Approximate brightness value based on **normalized** RGB values.
 * 
 * This method uses the approximation algorithm proposed in
 * https://www.w3.org/TR/AERT/#color-contrast.
 * The approximated value is normalized to a scale of 0 to 255.
 * 
 * @param red normalized red value
 * @param green normalized green value
 * @param blue normalized blue value
 * @return double approximation for color value
 */
double calculateBrightness(double red, double green, double blue) {
  const double RED_FACTOR = 0.299;
  const double GREEN_FACTOR = 0.587;
  const double BLUE_FACTOR = 0.114;

  double brightness = RED_FACTOR * red + GREEN_FACTOR * green + BLUE_FACTOR * blue;
  double normalizedBrightness = min(MAX_COLOR_VALUE, brightness);
  return normalizedBrightness;
}

/**
 * @brief Determine if brightness value represents a white or a black chess
 *        field.
 *
 * Note that the room must be well-lit!
 * At a normalized ambient light of about 10.0 or lower white field will be interpreted as black.
 * 
 * @param brightness normalized brightness value
 * @return true if surface is white-ish
 * @return false if surface is black-ish
 */
bool isWhiteField(double brightness) {
  const double THRESHOLD = 100.0;
  return brightness >= THRESHOLD;
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
