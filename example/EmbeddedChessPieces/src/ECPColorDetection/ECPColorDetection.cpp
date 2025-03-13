#include "ECPColorDetection.h"

ECPColorDetection::ECPColorDetection(Dezibot &d) : dezibot(d) {};

void ECPColorDetection::calibrateFieldColor() {
    double whiteBrightness = calibrateColor(true);
    double blackBrightness = calibrateColor(false);

    double diff = whiteBrightness - blackBrightness;
    double offset = diff * 0.025; // placeholder

    isWhiteFieldTopThreshold = whiteBrightness + offset;
    isWhiteFieldBottomThreshold = whiteBrightness - offset;
    isBlackFieldTopThreshold = blackBrightness + offset;
    isBlackFieldBottomThreshold = blackBrightness - offset;
    //debug
    dezibot.display.clear();
    dezibot.display.println(isWhiteFieldTopThreshold);
    dezibot.display.println(whiteBrightness);
    dezibot.display.println(isWhiteFieldBottomThreshold);
    dezibot.display.println(isBlackFieldTopThreshold);
    dezibot.display.println(blackBrightness);
    dezibot.display.println(isBlackFieldBottomThreshold);
    delay(7500);
};

FieldColor ECPColorDetection::getFieldColor() {
    const double brightness = measureBrightness();

    if (isWhiteFieldTopThreshold <= brightness) {
        return UNAMBIGUOUS_BLACK_TO_WHITE;
    }
    if ((isWhiteFieldBottomThreshold <= brightness) && ((brightness < isWhiteFieldTopThreshold))) {
        return WHITE_FIELD;
    }
    if ((isBlackFieldBottomThreshold < brightness) && ((brightness <= isBlackFieldTopThreshold))) {
        return BLACK_FIELD;
    }
    if (brightness <= isBlackFieldBottomThreshold) {
        return UNAMBIGUOUS_WHITE_TO_BLACK;
    }
    return UNAMBIGUOUS;
};

void ECPColorDetection::setShouldTurnOnColorCorrectionLight(bool turnOn) {
    shouldTurnOnColorCorrectionLight = turnOn;
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
    dezibot.display.clear();

    return measureBrightness();
};

double ECPColorDetection::measureBrightness() {
    if (shouldTurnOnColorCorrectionLight) {
        turnOnColorCorrectionLight();
        delay(DELAY_BEFORE_MEASURING);
    }

    const double ambient = dezibot.colorSensor.getNormalizedAmbientValue();
    double red = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::RED, ambient);
    double green = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::GREEN, ambient);
    double blue = dezibot.colorSensor.getNormalizedColorValue(ColorSensor::BLUE, ambient);

    turnOffColorCorrectionLight();

    return dezibot.colorSensor.calculateBrightness(red, green, blue);
};
