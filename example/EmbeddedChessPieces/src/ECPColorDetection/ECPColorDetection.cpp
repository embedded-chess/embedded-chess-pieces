#include "ECPColorDetection.h"

ECPColorDetection::ECPColorDetection(
    Dezibot &d, 
    ECPSignalDetection &ir
) : dezibot(d), ecpSignalDetection(ir) {};

void ECPColorDetection::calibrateFieldColor() {
    double minWhiteBrightness = MAX_NORMALIZED_COLOR_VALUE;
    double maxBlackBrightness = 0.0;

    for (size_t i = 0; i < CALIBRATE_FIELD_COUNT; i++) {
        const double whiteBrightness = calibrateAndMeasureColor(true);
        const double blackBrightness = calibrateAndMeasureColor(false);

        if (whiteBrightness < minWhiteBrightness) {
            minWhiteBrightness = whiteBrightness;
        }
        if (maxBlackBrightness < blackBrightness) {
            maxBlackBrightness = blackBrightness;
        }
    }

    double offsetWhite = minWhiteBrightness * THRESHOLD_OFFSET;
    double offsetBlack = maxBlackBrightness * 2 * THRESHOLD_OFFSET;

    thresholdIsWhiteField = minWhiteBrightness - offsetWhite;
    thresholdIsBlackField = maxBlackBrightness + offsetBlack;
};

void ECPColorDetection::calibrateIRFieldColor() {
    const float irWhiteValue = calibrateAndMeasureIRColor(true);
    const float irBlackValue = calibrateAndMeasureIRColor(false);

    float diff =  irWhiteValue - irBlackValue;
    float offset = diff * THRESHOLD_OFFSET_IR;

    thresholdIsIRWhiteField = irWhiteValue - offset;
    thresholdIsIRBlackField = irBlackValue + offset;
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

void ECPColorDetection::setUseInfraredColorDetection(bool useIR) {
    useInfraredColorDetection = useIR;
};

bool ECPColorDetection::getUseInfraredColorDetection() {
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

double ECPColorDetection::calibrateAndMeasureColor(bool isWhite) {
    const String color = isWhite ? "white" : "black";
    const String request = "Calibrate " + color + "\nPlease place on\n" + color 
        + " field\nwithin " + String(CALIBRATION_TIME / 1000) + "s";
    dezibot.display.clear();
    dezibot.display.println(request);
    delay(CALIBRATION_TIME);
    dezibot.display.clear();

    return measureBrightness();
};

float ECPColorDetection::calibrateAndMeasureIRColor(bool isWhite) {
    const String color = isWhite ? "white" : "black";
    const String request = "Calibrate " + color + "\nPlease place on\n" + color
        + " field\nwithin " + String((CALIBRATION_TIME) / 1000) + "s";
    dezibot.display.clear();
    dezibot.display.println(request);
    delay(CALIBRATION_TIME);
    
    const float irValue = ecpSignalDetection.cumulateInfraredValues();

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

    if (thresholdIsWhiteField <= brightness) {
        return WHITE_FIELD;
    }
    if (brightness <= thresholdIsBlackField) {
        return BLACK_FIELD;
    }
    return AMBIGUOUS;
};

FieldColor ECPColorDetection::calculateLikelyFieldColor() {
    const double brightness = measureBrightness();

    int diffToWhite = std::abs(thresholdIsWhiteField - brightness);
    int diffToBlack = std::abs(brightness - thresholdIsBlackField);

    return diffToWhite < diffToBlack ? WHITE_FIELD : BLACK_FIELD;
};

FieldColor ECPColorDetection::measureInfraredFieldColor() {
    const float irValue = ecpSignalDetection.cumulateInfraredValues();

    if (thresholdIsIRWhiteField < irValue) {
        return WHITE_FIELD;
    }
    if (irValue < thresholdIsIRBlackField) {
        return BLACK_FIELD;
    }

    return AMBIGUOUS;
};

FieldColor ECPColorDetection::calculateLikelyInfraredFieldColor() {
    const float irValue = ecpSignalDetection.cumulateInfraredValues();

    float diffToWhite = std::abs(thresholdIsIRWhiteField - irValue);
    float diffToBlack = std::abs(irValue - thresholdIsIRBlackField);

    return diffToWhite < diffToBlack ? WHITE_FIELD : BLACK_FIELD;
};
