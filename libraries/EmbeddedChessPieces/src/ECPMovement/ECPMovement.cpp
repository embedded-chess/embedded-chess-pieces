#include "ECPMovement.h"

ECPMovement::ECPMovement(Dezibot &d, uint mc = DEFAULT_MOVEMENT_CALIBRATION)
    : dezibot(d),
      ecpColorDetection(ECPColorDetection(d)),
      movementCalibration(mc) {};

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

void ECPMovement::moveToNextField() {
    bool startedOnWhite = ecpColorDetection.isWhiteField();
    bool currentlyOnWhite = startedOnWhite;

    while (currentlyOnWhite == startedOnWhite) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentlyOnWhite = ecpColorDetection.isWhiteField();
    }
};

void ECPMovement::move(uint numberOfFields) {
    for (size_t i = 0; i < numberOfFields; i++) {
        moveToNextField();
    }
};
