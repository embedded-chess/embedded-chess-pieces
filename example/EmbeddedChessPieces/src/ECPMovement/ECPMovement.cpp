#include "ECPMovement.h"

ECPMovement::ECPMovement(
    Dezibot &d, 
    uint mc = DEFAULT_MOVEMENT_CALIBRATION, 
    uint rtl = DEFAULT_ROTATION_TIME_LEFT, 
    uint rtr = DEFAULT_ROTATION_TIME_RIGHT
) : dezibot(d),
    ecpColorDetection(ECPColorDetection(d)),
    movementCalibration(mc),
    rotationTimeLeft(rtl),
    rotationTimeRight(rtr) {};

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

void ECPMovement::moveToNextField() {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();
    bool isCurrentlyOnWhite = hasStartedOnWhite;

    while (isCurrentlyOnWhite == hasStartedOnWhite) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    }
};

void ECPMovement::move(uint numberOfFields) {
    for (size_t i = 0; i < numberOfFields; i++) {
        moveToNextField();
    }
};

void ECPMovement::turnLeft() {
    dezibot.motion.right.setSpeed(ROTATION_SPEED);
    delay(rotationTimeLeft);
    dezibot.motion.right.setSpeed(0);
    delay(MOVEMENT_BREAK);
};

void ECPMovement::turnRight() {
    dezibot.motion.left.setSpeed(ROTATION_SPEED);
    delay(rotationTimeRight);
    dezibot.motion.left.setSpeed(0);
    delay(MOVEMENT_BREAK);
};
