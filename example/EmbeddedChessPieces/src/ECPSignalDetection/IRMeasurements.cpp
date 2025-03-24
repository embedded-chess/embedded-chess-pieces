#include "ECPSignalDetection.h"

IRMeasurements::IRMeasurements(float north, float east, float south, float west) 
    : north(north), east(east), south(south), west(west) {};

bool IRMeasurements::hasSignal() {
    bool hasSignal = north > MIN_THRESHOLD_MEASUREMENTS 
        || east > MIN_THRESHOLD_MEASUREMENTS 
        || south > MIN_THRESHOLD_MEASUREMENTS 
        || west > MIN_THRESHOLD_MEASUREMENTS;

    return hasSignal;
};

float IRMeasurements::getSum() {
    return north + east + south + west;
};
