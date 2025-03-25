#include "ECPMovement.h"

ECPMovement::ECPMovement(
    Dezibot &dezibot,
    uint movementCalibration
) : dezibot(dezibot),
    ecpSignalDetection(ECPSignalDetection(dezibot)),
    ecpColorDetection(ECPColorDetection(dezibot, ecpSignalDetection)),
    movementCalibration(movementCalibration) {};

void ECPMovement::move(
    uint numberOfFields, 
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    for (size_t i = 0; i < numberOfFields; i++) {
        bool wasSuccessfulMovement = moveToNextField();
        
        if (!wasSuccessfulMovement) {
            // request position to the final destination
            displayForwardMovementCorrectionRequest(
                intendedField,
                intendedDirection
            );

            // end further movement
            break;
        }
    }
};

void ECPMovement::turnLeft(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const FieldColor startColor = ecpColorDetection.getFieldColor();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();
    
    // if dezibot initially faces 270°, subtract 90° to turn left, resulting
    // in the dezibot facing 180°
    // add 360 before applying modulo to prevent negative values
    const int goalAngle = (initialAngle - 90 + 360) % 360;
    
    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const FieldColor currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor || !wasRotationSuccessful) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::turnRight(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const FieldColor startColor = ecpColorDetection.getFieldColor();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();

    // if dezibot initially faces 180°, add 90° to turn left, resulting
    // in the dezibot facing 270°
    const int goalAngle = (initialAngle + 90) % 360;

    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const FieldColor currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor || !wasRotationSuccessful) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::calibrateFieldColor() {
    ecpColorDetection.calibrateFieldColor();
};

void ECPMovement::calibrateIRFieldColor() {
    ecpColorDetection.calibrateIRFieldColor();
};

void ECPMovement::setUseInfraredColorDetection(bool useIR) {
    ecpColorDetection.setUseInfraredColorDetection(useIR);
};

void ECPMovement::setShouldTurnOnColorCorrectionLight(bool turnOn) {
    ecpColorDetection.setShouldTurnOnColorCorrectionLight(turnOn);
};

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void ECPMovement::moveForward(int timeMovement) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
};

bool ECPMovement::moveToNextField() {
    FieldColor startColor = ecpColorDetection.getFieldColor();
    if (startColor == AMBIGUOUS) {
        startColor = ecpColorDetection.getLikelyFieldColor();
    }
    
    const FieldColor wantedColor = startColor == BLACK_FIELD ? 
        WHITE_FIELD : BLACK_FIELD;
    FieldColor currentColor = startColor;
    int currentIteration = 0;

    while (currentColor != wantedColor) {
        if (currentIteration == MAX_ITERATIONS) {
            return false;
        }
        currentIteration++;

        moveForward(FORWARD_TIME);
        currentColor = ecpColorDetection.getFieldColor();
    }

    return true;
};

void ECPMovement::displayRotationCorrectionRequest(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty rotation\nPlease correct\nmy position\nwithin " 
        + String(MANUAL_CORRECTION_TIME / 1000) + "s to\n\n> " 
        + currentField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUAL_CORRECTION_TIME);
    dezibot.display.clear();
};

void ECPMovement::displayForwardMovementCorrectionRequest(
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty movement\nPlease correct\nmy position\nwithin " 
        + String(MANUAL_CORRECTION_TIME / 1000) + "s to\n\n> " 
        + intendedField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUAL_CORRECTION_TIME);
    dezibot.display.clear();
};

bool ECPMovement::rotateToAngle(int goalAngle, int initialAngle) {
    int currentAngle = initialAngle;
    int difference = goalAngle - currentAngle;
    size_t currentIteration = 0;

    bool shouldContinueRotation = std::abs(difference) > ROTATION_TOLERANCE
        && currentIteration < MAX_ITERATIONS;

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
            && currentIteration < MAX_ITERATIONS;
    }

    if (currentIteration == MAX_ITERATIONS) {
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
