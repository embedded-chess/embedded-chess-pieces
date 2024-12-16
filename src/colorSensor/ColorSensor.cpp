#include "ColorSensor.h"

bool ColorSensor::begin() {
    bool hasStartedSuccessfully = rgbwSensor.begin();
    if (!hasStartedSuccessfully) {
        return false;
    }

    uint8_t configuration = VEML6040_IT_320MS;  // 320 ms integration time
    configuration += VEML6040_AF_AUTO;          // auto mode
    configuration += VEML6040_SD_ENABLE;        // enable color sensor
    rgbwSensor.setConfiguration(configuration);
    return true;
};

double ColorSensor::getNormalizedAmbientValue() {
    double ambient = rgbwSensor.getAmbientLight();  // ambient light in lux
    double normalizedValue = ambient / MAX_RAW_AMBIENT_VALUE * MAX_NORMALIZED_COLOR_VALUE;
    return normalizedValue;
};

double ColorSensor::getRawColorValue(Color color) {
    switch (color) {
        case RED:
            return rgbwSensor.getRed();
        case GREEN:
            return rgbwSensor.getGreen();
        case BLUE:
            return rgbwSensor.getBlue();
        case WHITE:
            return rgbwSensor.getWhite();
    }
};

double ColorSensor::getNormalizedColorValue(Color color, double normalizedAmbientLight) {
    double colorValue = getRawColorValue(color);
    double normalizedValue = colorValue * normalizedAmbientLight / MAX_RGBW_SENSOR_VALUE * MAX_NORMALIZED_COLOR_VALUE;
    normalizedValue = std::min(MAX_NORMALIZED_COLOR_VALUE, normalizedValue);
    return normalizedValue;
};

double ColorSensor::getCCT() {
    return rgbwSensor.getCCT() * 1.0;
};

double ColorSensor::calculateBrightness(double red, double green, double blue) {
    const double RED_FACTOR = 0.299;
    const double GREEN_FACTOR = 0.587;
    const double BLUE_FACTOR = 0.114;

    double brightness = RED_FACTOR * red + GREEN_FACTOR * green + BLUE_FACTOR * blue;
    double normalizedBrightness = std::min(MAX_NORMALIZED_COLOR_VALUE, brightness);
    return normalizedBrightness;
};
