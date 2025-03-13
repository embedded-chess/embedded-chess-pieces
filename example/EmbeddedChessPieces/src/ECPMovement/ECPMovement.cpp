#include "ECPMovement.h"

ECPMovement::ECPMovement(
    Dezibot &dezibot,
    uint movementCalibration
) : dezibot(dezibot),
    ecpColorDetection(ECPColorDetection(dezibot)),
    ecpSignalDetection(ECPSignalDetection(dezibot)),
    movementCalibration(movementCalibration) {};

void ECPMovement::move(
    uint numberOfFields, 
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    for (size_t i = 0; i < numberOfFields; i++) {
        bool successfulMovement = moveToNextField();
        
        if (!successfulMovement) {
            displayForwardMovementCorrectionRequest(
                intendedField, 
                intendedDirection
            );
            break;
        }
    }
};

void ECPMovement::turnLeft(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const int startColor = ecpColorDetection.getFieldColor();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();
    
    // if dezibot initially faces 270°, subtract 90° to turn left, resulting
    // in the dezibot facing 180°
    // add 360 before applying modulo to prevent negative values
    const int goalAngle = (initialAngle - 90 + 360) % 360;
    
    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const int currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor || !wasRotationSuccessful) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::turnRight(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const int startColor = ecpColorDetection.getFieldColor();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();

    // if dezibot initially faces 180°, add 90° to turn left, resulting
    // in the dezibot facing 270°
    const int goalAngle = (initialAngle + 90) % 360;

    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const int currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor || !wasRotationSuccessful) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

ECPColorDetection* ECPMovement::getECPColorDetection() {
    return &ecpColorDetection;
}

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

bool ECPMovement::moveToNextField() {
    const int startColor = ecpColorDetection.getFieldColor();
    const int wantedColor = startColor == 1 ? startColor + 1 : startColor -1;
    const int stopoverColor = wantedColor + 2;
    int currentColor = startColor;
    int currentIteration = 0;

    // reach middle of the next field with the front leg
    while (currentColor != stopoverColor) {
        if (currentIteration == MAX_ITERATIONS) {
            return false;
        }
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
        currentIteration++;
    }

    // move further to place the whole dezibot on the field
    while (currentColor != wantedColor) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
        if (currentColor == 4) { // unambiguous
            return false;
        }
    }

    return true;
};

void ECPMovement::displayRotationCorrectionRequest(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty rotation\nPlease correct\nmy position in\n" 
        + String(MANUEL_CORRECTION_TIME/1000) + " seconds to\n\n> " 
        + currentField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUEL_CORRECTION_TIME);
    dezibot.display.clear();
};

void ECPMovement::displayForwardMovementCorrectionRequest(
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty movement\nPlease correct\nmy position in\n" 
        + String(MANUEL_CORRECTION_TIME/1000) + " seconds to\n\n> " 
        + intendedField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUEL_CORRECTION_TIME);
    dezibot.display.clear();
};

bool ECPMovement::rotateToAngle(int goalAngle, int initialAngle) {
    int currentAngle = initialAngle;
    int difference = goalAngle - currentAngle;
    size_t currentIteration = 0;

    bool shouldContinueRotation = std::abs(difference) > ROTATION_TOLERANCE
        && currentIteration < MAX_ROTATION_ITERATIONS;

    while (shouldContinueRotation) {
        int normalizedDifference = ((difference + 180 + 360) % 360) - 180;
        uint rotationTime = calculateRotationTime(normalizedDifference);

        if (normalizedDifference == 0 || normalizedDifference == -180) {
            // exactly opposed to goal angle, rotation direction does not matter
            rotateLeft(rotationTime);
        } else if (normalizedDifference < 0) {
            rotateLeft(rotationTime);
        } else {
            rotateRight(rotationTime);
        }

        delay(MEASURING_DELAY); // for better measuring results
        currentAngle = ecpSignalDetection.measureDezibotAngle();

        difference = goalAngle - currentAngle;
        
        currentIteration++;
        shouldContinueRotation = std::abs(difference) > ROTATION_TOLERANCE
            && currentIteration < MAX_ROTATION_ITERATIONS;
    }

    if (currentIteration == MAX_ROTATION_ITERATIONS) {
        // rotation failed
        return false;
    }

    // rotation successful
    return true;
};

void ECPMovement::rotateLeft(uint movementTime) {
    dezibot.motion.right.setSpeed(ROTATION_SPEED);
    delay(movementTime);
    dezibot.motion.right.setSpeed(0);
};

void ECPMovement::rotateRight(uint movementTime) {
    dezibot.motion.left.setSpeed(ROTATION_SPEED);
    delay(movementTime);
    dezibot.motion.left.setSpeed(0);
};

uint ECPMovement::calculateRotationTime(int normalizedAngleDifference) {
    float rotationTime = ROTATION_TIME_FACTOR * std::abs(normalizedAngleDifference);
    return std::round(rotationTime);
};
