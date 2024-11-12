#include "ECPMovement.h"

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, CALIBRATION_STRAIGHT);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

void ECPMovement::moveToNextField(bool isOnWhite) {
    bool isWhiteField = isOnWhite;

    while (isWhiteField == isOnWhite) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);

        isWhiteField = ecpColorDetection.isWhiteField();
    }
};

void ECPMovement::move() {
    // Placeholder
    bool isOnWhite = ecpColorDetection.isWhiteField();
    moveToNextField(isOnWhite);
};
