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

    bool hasSignal = std::any_of(
        values, values+4,
        [MIN_THRESHOLD_MEASUREMENTS](float value) {
            return value > MIN_THRESHOLD_MEASUREMENTS;
        }
    );

    if (!hasSignal) {
        return -1.0f;
    }

    const float north = values[0];
    const float east = values[1];
    const float south = values[2];
    const float west = values[3];

    const float resultantNorthSouth = north - south;
    const float resultantEastWest = east - west;

    float angle = std::atan2(resultantEastWest, resultantNorthSouth);
    angle *= (180.0f / M_PI);   // convert from radian to degrees
    
    // normalize angle to [0, 360]
    if (angle < 0) {
        angle += 360.0f;
    }

    return std::round(angle);
};
