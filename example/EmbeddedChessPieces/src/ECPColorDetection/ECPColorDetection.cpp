#include "ECPColorDetection.h"

ECPColorDetection::ECPColorDetection(
    Dezibot &d, 
    ECPSignalDetection &ir
) : dezibot(d), ecpSignalDetection(ir) {};

void ECPColorDetection::calibrateFieldColor() {
    double minWhiteBrightness = MAX_NORMALIZED_COLOR_VALUE;
    double maxBlackBrightness = 0.0;

    for (size_t i = 0; i < CALIBRATE_FIELD_COUNT; i++) {
        const double whiteBrightness = calibrateColor(true);
        const double blackBrightness = calibrateColor(false);

        if (whiteBrightness < minWhiteBrightness) {
            minWhiteBrightness = whiteBrightness;
        }
        if (maxBlackBrightness < blackBrightness) {
            maxBlackBrightness = blackBrightness;
        }
    }

    double offsetWhite = minWhiteBrightness * THRESHOLD_OFFSET;
    double offsetBlack = maxBlackBrightness * 2 * THRESHOLD_OFFSET; 

    isWhiteFieldThreshold = minWhiteBrightness - offsetWhite;
    isBlackFieldThreshold = maxBlackBrightness + offsetBlack;
};

void ECPColorDetection::calibrateIRFieldColor() {
    const int irWhiteValue = calibrateIRColor(true);
    const int irBlackValue = calibrateIRColor(false);

    int diff =  irWhiteValue - irBlackValue;
    double offset = ((double) diff) * THRESHOLD_OFFSET_IR;

    isIRWhiteFieldThreshold = irWhiteValue - offset;
    isIRBlackFieldThreshold = irBlackValue + offset;
};

FieldColor ECPColorDetection::getFieldColor() {
    if (useInfraredColorDetection) {
        return measureInfraredFieldColor();
    }
    
    return measureFieldColor();
};

FieldColor ECPColorDetection::getLikelyFieldColor() {
    if (useInfraredColorDetection) {
        return calculateLikelyInfraredFieldColor();
    }
    
    return calculateLikelyFieldColor();
};

void ECPColorDetection::setColorDetectionMode(bool useIR) {
    useInfraredColorDetection = useIR;
};

bool ECPColorDetection::getColorDetectionMode() {
    return useInfraredColorDetection;
};

void ECPColorDetection::setShouldTurnOnColorCorrectionLight(bool turnOn) {
    shouldTurnOnColorCorrectionLight = turnOn;
};

bool ECPColorDetection::getShouldTurnOnColorCorrectionLight() {
    return shouldTurnOnColorCorrectionLight;
};

void ECPColorDetection::turnOnColorCorrectionLight() {
    uint32_t colorCorrectionWhite = dezibot.multiColorLight.color(
        COLOR_CORRECTION_LIGHT_R,
        COLOR_CORRECTION_LIGHT_G,
        COLOR_CORRECTION_LIGHT_B
    );
    dezibot.multiColorLight.setLed(BOTTOM, colorCorrectionWhite);
};

void ECPColorDetection::turnOffColorCorrectionLight() {
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

double ECPColorDetection::calibrateColor(bool isWhite) {
    const String color = isWhite ? "white" : "black";
    const String request = "Calibrate " + color + "\nPlease place on\n" + color 
        + " field\nin " + String(CALIBRATION_TIME / 1000) + " seconds";
    dezibot.display.clear();
    dezibot.display.println(request);
    delay(CALIBRATION_TIME);
    dezibot.display.clear();

    return measureBrightness();
};

int ECPColorDetection::calibrateIRColor(bool isWhite) {
    const String color = isWhite ? "white" : "black";
    const String request = "Calibrate " + color + "\nPlease place on\n" + color
        + " field\nin " + String((CALIBRATION_TIME) / 1000) + " seconds"; // TODO: use constant
    dezibot.display.clear();
    dezibot.display.println(request);
    delay(CALIBRATION_TIME);
    
    const int irValue = ecpSignalDetection.cumulateInfraredValues();

    // clear display after measuring irValue
    dezibot.display.clear();

    return irValue;
};

double ECPColorDetection::measureBrightness() {
    if (shouldTurnOnColorCorrectionLight) {
        turnOnColorCorrectionLight();
    }

    double cumulatedBrightness = 0.0;

    for (size_t i = 0; i < MEASUREMENT_COUNT; i++) {
        delay(DELAY_BEFORE_MEASURING);

        const double ambient = dezibot.colorSensor.getNormalizedAmbientValue();
        double red = dezibot.colorSensor.getNormalizedColorValue(
            ColorSensor::RED, 
            ambient
        );
        double green = dezibot.colorSensor.getNormalizedColorValue(
            ColorSensor::GREEN, 
            ambient
        );
        double blue = dezibot.colorSensor.getNormalizedColorValue(
            ColorSensor::BLUE, 
            ambient
        );

        cumulatedBrightness += dezibot.colorSensor.calculateBrightness(
            red, 
            green, 
            blue
        );
    }
    
    turnOffColorCorrectionLight();

    return cumulatedBrightness / ((double) MEASUREMENT_COUNT);
};

FieldColor ECPColorDetection::measureFieldColor() {
    const double brightness = measureBrightness();

    if (isWhiteFieldThreshold <= brightness) {
        return WHITE_FIELD;
    }
    if (brightness <= isBlackFieldThreshold) {
        return BLACK_FIELD;
    }
    return UNAMBIGUOUS;
};

FieldColor ECPColorDetection::calculateLikelyFieldColor() {
    const double brightness = measureBrightness();

    int diffToWhite = std::abs(isWhiteFieldThreshold - brightness);
    int diffToBlack = std::abs(brightness - isBlackFieldThreshold);

    int smaller = std::min(diffToWhite, diffToBlack);

    return diffToBlack == smaller ? BLACK_FIELD : WHITE_FIELD;
};

FieldColor ECPColorDetection::measureInfraredFieldColor() {
    const int irValue = ecpSignalDetection.cumulateInfraredValues();

    if (isIRWhiteFieldThreshold < irValue) {
        return WHITE_FIELD;
    }
    if (irValue < isIRBlackFieldThreshold) {
        return BLACK_FIELD;
    }

    return UNAMBIGUOUS;
};

FieldColor ECPColorDetection::calculateLikelyInfraredFieldColor() {
    const int irValue = ecpSignalDetection.cumulateInfraredValues();

    int diffToWhite = std::abs(isIRWhiteFieldThreshold - irValue);
    int diffToBlack = std::abs(irValue - isBlackFieldThreshold);

    int smaller = std::min(diffToWhite, diffToBlack);

    return diffToBlack == smaller ? BLACK_FIELD : WHITE_FIELD;
};
