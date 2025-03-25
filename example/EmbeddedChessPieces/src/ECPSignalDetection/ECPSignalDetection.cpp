#include "ECPSignalDetection.h"

ECPSignalDetection::ECPSignalDetection(Dezibot &dezibot)
    : dezibot(dezibot) {};

int ECPSignalDetection::measureSignalAngle() {
    IRMeasurements measurements = measureIR();

    // repeat if no sufficient signal could be measured
    if (!measurements.hasSignal()) {
        dezibot.display.clear();
        dezibot.display.println("No IR signal!");
        dezibot.display.println("Trying again...");
        delay(500);
        dezibot.display.clear();
        return measureSignalAngle();
    }

    // calculate angle
    const float resultantX = measurements.east - measurements.west;
    const float resultantY = measurements.north - measurements.south;
    float angle = std::atan2(resultantX, resultantY);
    angle *= (180.0f / M_PI);   // convert from radian to degrees

    int roundedAngle = std::round(angle);

    // normalize angle to [0, 360]
    // add 360° before applying modulo to prevent negative values
    roundedAngle = (roundedAngle + 360) % 360;

    return roundedAngle;
};

int ECPSignalDetection::measureDezibotAngle() {
    int signalAngle = measureSignalAngle();
    return (360 - signalAngle) % 360;
};

float ECPSignalDetection::cumulateInfraredValues(bool turnOnIRLight) {
    // check for interfering infrared signal
    IRMeasurements measurements = measureIR();

    // repeat if interfering signal was measured
    if (measurements.hasSignal()) {
        dezibot.display.clear();
        dezibot.display.println("Interfering IR\nsignal!");
        dezibot.display.println("Trying again...");
        delay(500);
        dezibot.display.clear();
        return cumulateInfraredValues(turnOnIRLight);
    }

    if (turnOnIRLight) {
        dezibot.infraredLight.bottom.turnOn();
        delay(DELAY_IR_INTERACTION);

        IRMeasurements measurements = measureIR();

        dezibot.infraredLight.bottom.turnOff();
        delay(DELAY_IR_INTERACTION);

        return measurements.getSum();
    }

    return measurements.getSum();
};

IRMeasurements ECPSignalDetection::measureIR() {
    const photoTransistors sensors[] = { IR_FRONT, IR_RIGHT, IR_BACK, IR_LEFT };
    float values[4] = {};

    // measure all four IR signal values
    for (size_t i = 0; i < 4; i++) {
        const int irValue = dezibot.lightDetection.getAverageValue(
            sensors[i],
            MEASUREMENT_COUNT,
            TIME_BETWEEN_MEASUREMENTS
        );
        const float normalizedValue = dezibot.lightDetection.normalizeValue(irValue);
        values[i] = normalizedValue;
    }
    
    IRMeasurements measurements = { values[0], values[1], values[2], values[3] };
    return measurements;
};
