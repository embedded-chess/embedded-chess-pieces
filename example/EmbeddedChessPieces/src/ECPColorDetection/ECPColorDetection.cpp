#include "ECPColorDetection.h"

ECPColorDetection::ECPColorDetection(Dezibot &d) : dezibot(d) {};

void ECPColorDetection::calibrateFieldColor() {
    double whiteBrightness = calibrateColor(true);
    double blackBrightness = calibrateColor(false);

    double diff = whiteBrightness - blackBrightness;
    double offset = diff * 0.3; // placeholder

    isWhiteFieldThreshold = whiteBrightness - offset;
    isBlackFieldThreshold = blackBrightness + offset;
};

FieldColor ECPColorDetection::getFieldColor() {
    const double ambient = dezibot.colorSensor.getNormalizedAmbientValue();
    double red = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::RED, ambient);
    double green = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::GREEN, ambient);
    double blue = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::BLUE, ambient);

    const double brightness = dezibot.colorSensor.calculateBrightness(red, green, blue);

    if (brightness >= isWhiteFieldThreshold) {
        return WHITE_FIELD;
    }
    if (brightness <= isBlackFieldThreshold) {
        return BLACK_FIELD;
    }
    return UNAMBIGUOUS_FIELD;
};

void ECPColorDetection::setShouldTurnOnColorCorrectionLight(bool turnOn) {
    shouldTurnOnColorCorrectionLight = turnOn;
    turnOn ? turnOnColorCorrectionLight() : turnOffColorCorrectionLight();
}

bool ECPColorDetection::getShouldTurnOnColorCorrectionLight() {
    return shouldTurnOnColorCorrectionLight;
}

void ECPColorDetection::turnOnColorCorrectionLight() {
    uint32_t colorCorrectionWhite = dezibot.multiColorLight.color(
        COLOR_CORRECTION_LIGHT_R,
        COLOR_CORRECTION_LIGHT_G,
        COLOR_CORRECTION_LIGHT_B);
    dezibot.multiColorLight.setLed(BOTTOM, colorCorrectionWhite);
};

void ECPColorDetection::turnOffColorCorrectionLight() {
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

double ECPColorDetection::calibrateColor(bool isWhite) {
    String color = isWhite ? "white" : "black";
    String request = "Calibrate " + color + "\nPlease place on\n" + color + 
        " field\nin " + String(CALIBRATION_TIME/1000) + " seconds";
    dezibot.display.clear();
    dezibot.display.println(request);
    delay(CALIBRATION_TIME);

    double ambient = dezibot.colorSensor.getNormalizedAmbientValue();
    double red = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::RED, ambient);
    double green = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::GREEN, ambient);
    double blue = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::BLUE, ambient);
    dezibot.display.clear();

    double brightness = dezibot.colorSensor.calculateBrightness(red, green, blue);
    return brightness;
};
