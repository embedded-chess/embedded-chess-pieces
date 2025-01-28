#include "ECPMovement.h"

ECPMovement::ECPMovement(
  Dezibot &dezibot,
  uint movementCalibration,
  uint rotationTimeLeft,
  uint rotationTimeRight
) : dezibot(dezibot),
    ecpColorDetection(ECPColorDetection(dezibot)),
    movementCalibration(movementCalibration),
    rotationTimeLeft(rotationTimeLeft),
    rotationTimeRight(rotationTimeRight) {};

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

void ECPMovement::turnLeft(String currentField, String intendedDirection) {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();

    dezibot.motion.right.setSpeed(ROTATION_SPEED);
    delay(rotationTimeLeft);
    dezibot.motion.right.setSpeed(0);
    delay(MOVEMENT_BREAK);
    
    bool isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    if (isCurrentlyOnWhite != hasStartedOnWhite) {
        displayRotionCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::turnRight(String currentField, String intendedDirection) {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();

    dezibot.motion.left.setSpeed(ROTATION_SPEED);
    delay(rotationTimeRight);
    dezibot.motion.left.setSpeed(0);
    delay(MOVEMENT_BREAK);

    bool isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    if (isCurrentlyOnWhite != hasStartedOnWhite) {
        displayRotionCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::displayRotionCorrectionRequest(
    String currentField, 
    String intendedDirection
) {
    String request = "Faulty rotation\nPlease correct\nmy position in\n10 seconds to\n\n> " + currentField + " " + intendedDirection + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(10000);
    dezibot.display.clear();
}
