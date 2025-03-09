#include "ECPSignalDetection.h"

ECPSignalDetection::ECPSignalDetection(Dezibot &dezibot)
    : dezibot(dezibot) {};

int ECPSignalDetection::measureSignalAngle() {
    const photoTransistors sensors[] = { IR_FRONT, IR_RIGHT, IR_BACK, IR_LEFT };
    float values[4] = {};

    for (size_t i = 0; i < 4; i++) {
        const int irValue = dezibot.lightDetection.getAverageValue(
            sensors[i],
            MEASUREMENT_COUNT,
            TIME_BETWEEN_MEASUREMENTS
        );
        const float normalizedValue = dezibot.lightDetection.normalizeValue(irValue);
        values[i] = normalizedValue;
    }

    // check if at least one of the measurements is above the threshold
    bool hasSignal = std::any_of(
        values, values+4,
        [MIN_THRESHOLD_MEASUREMENTS](float value) {
            return value > MIN_THRESHOLD_MEASUREMENTS;
        }
    );

    // recurse if no significant signal could be measured
    if (!hasSignal) {
        dezibot.display.clear();
        dezibot.display.println("No IR signal!");
        dezibot.display.println("Trying again...");
        delay(1000);
        return measureSignalAngle();
    }

    const float north = values[0];
    const float east = values[1];
    const float south = values[2];
    const float west = values[3];

    const float resultantNorthSouth = north - south;
    const float resultantEastWest = east - west;

    float angle = std::atan2(resultantEastWest, resultantNorthSouth);
    angle *= (180.0f / M_PI);   // convert from radian to degrees

    int roundedAngle = std::round(angle);

    // normalize angle to [0, 360]
    roundedAngle = roundedAngle % 360;
    if (roundedAngle < 0) {
        roundedAngle += 360;
    }

    return roundedAngle;
};

int ECPSignalDetection::measureDezibotAngle() {
    int signalAngle = measureSignalAngle();
    return (360 - signalAngle) % 360;
}
