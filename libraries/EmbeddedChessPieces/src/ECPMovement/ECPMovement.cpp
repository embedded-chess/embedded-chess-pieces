#include "ECPMovement.h"

ECPMovement::ECPMovement(Dezibot &d, uint mc = 3900) : dezibot(d), ecpColorDetection(d) {
    movementCalibration = mc;
};

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

void ECPMovement::move(uint numberOfFields) {
    // Placeholder
    bool isOnWhite = false;
    while (numberOfFields > 0) {
        isOnWhite = ecpColorDetection.isWhiteField();
        moveToNextField(isOnWhite);
        numberOfFields--;
    }
};
