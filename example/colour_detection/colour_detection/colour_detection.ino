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

// Get normalized value of ambient light sensor on a scale from 0 to 255.
double getNormalizedAmbientValue() {
  const double MAX_AMBIENT_VALUE = 2061.0;

  // ambient light in lux
  double ambient = rgbwSensor.getAmbientLight();
  double normalizedValue = ambient / MAX_AMBIENT_VALUE * MAX_COLOR_VALUE;
  return normalizedValue;
}

// Get raw color value of VEML sensor (**not** normalized!).
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

// Get normalize value of VEML color sensor on a scale of 0 to 255 based on
// ambient lighting conditions.
double getNormalizedColorValue(color color, double ambientLightValue) {
  const double MAX_SENSOR_VALUE = 65535.0;

  double colorValue = getRawColorValue(color);
  double normalizedValue = colorValue * ambientLightValue / MAX_SENSOR_VALUE * MAX_COLOR_VALUE;
  normalizedValue = min(MAX_COLOR_VALUE, normalizedValue);
  return normalizedValue;
}

// Calculate brightness value based on **normalized** RGB values.
double calculateBrightness(double red, double green, double blue) {
  const double RED_FACTOR = 0.299;
  const double GREEN_FACTOR = 0.587;
  const double BLUE_FACTOR = 0.114;

  double brightness = RED_FACTOR * red + GREEN_FACTOR * green + BLUE_FACTOR * blue;
  double normalizedBrightness = min(MAX_COLOR_VALUE, brightness);
  return normalizedBrightness;
}

// Determine if brightness value represents a white or a black chess field.
// Note that the room must be well-lit.
bool isWhiteField(double brightness) {
  const double THRESHOLD = 100.0;
  return brightness >= THRESHOLD;
}

// Print passed color value to dezibot display and serial monitor.
void printValue(double colorValue, char* prefix) {
  dezibot.display.print(prefix);
  dezibot.display.print(" ");
  dezibot.display.println(String(colorValue, 4));

  Serial.print(prefix);
  Serial.print(" ");
  Serial.println(colorValue);
}

// Print formatted info for isWhiteField.
void printIsWhiteField(bool isWhiteField) {
  dezibot.display.print("F ");
  Serial.print("F ");
  String field = isWhiteField ? "W" : "B";
  dezibot.display.println(field);
  Serial.println(field);
}
