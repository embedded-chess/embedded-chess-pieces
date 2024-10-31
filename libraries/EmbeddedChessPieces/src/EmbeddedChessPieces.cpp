#include "EmbeddedChessPieces.h"

double ECPColorDetection::isWhiteField() {
    double ambient = dezibot.colorSensor.getNormalizedAmbientValue();
    double red = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::RED, ambient);
    double green = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::GREEN, ambient);
    double blue = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::BLUE, ambient);
    double white = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::WHITE, ambient);

    double brightness = dezibot.colorSensor.calculateBrightness(red, green, blue);

    return brightness >= IS_WHITE_FIELD_THRESHOLD;
};

void ECPColorDetection::turnOnColorCorrectionLight() {
    uint32_t colorCorrectionWhite = dezibot.multiColorLight.color(
        COLOR_CORRECTION_LIGHT_R,
        COLOR_CORRECTION_LIGHT_G,
        COLOR_CORRECTION_LIGHT_B);
    dezibot.multiColorLight.setLed(BOTTOM, colorCorrectionWhite);
};

void ECPColorDetection::turnOffColorCorrectionLight() {
    dezibot.multiColorLight.setLed(BOTTOM, 0);
}
