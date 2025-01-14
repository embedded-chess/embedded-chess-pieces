#include "ECPChessPiece.h"

ECPChessPiece::ECPChessPiece(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : dezibot(d),
    ecpMovement(ecpMovement),
    currentField(initialField),
    isWhite(isWhite),
    currentDirection(isWhite ? NORTH : SOUTH) {};

bool ECPChessPiece::move(ECPChessField newField) {
    // show light depending on validity of requested movement
    if (isMoveValid(newField)) {
        setGreenLight(true);
        delay(COLOR_DELAY);
        setGreenLight(false);
    } else {
        setRedLight(true);
        delay(COLOR_DELAY);
        setRedLight(false);
        return false;
    }

    const int colDiff = (int) currentField.column - (int) newField.column;
    const int rowDiff = (int) currentField.row - (int) newField.row;

    if (colDiff != 0) {
        moveHorizontally(colDiff);
    }

    if (rowDiff != 0) {
        moveVertically(rowDiff);
    }

    currentField = newField;
    turnBackToInitialDirection();

    return true;
};

ECPChessField ECPChessPiece::getCurrentField() {
    return currentField;
};

void ECPChessPiece::moveHorizontally(int fieldsToMove) {
    const Direction newDirection = fieldsToMove > 0 ? WEST : EAST;

    // turn in the right direction if necessary
    switch (currentDirection) {
        case NORTH:
            newDirection == WEST ? ecpMovement.turnLeft() : ecpMovement.turnRight();
            break;
        case EAST:
            if (newDirection == WEST) {
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            }
            break;
        case SOUTH:
            newDirection == WEST ? ecpMovement.turnRight() : ecpMovement.turnLeft();
            break;
        case WEST:
            if (newDirection != WEST) {
                // turn around
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            }
    }

    currentDirection = newDirection;
    ecpMovement.move(abs(fieldsToMove));
};

void ECPChessPiece::moveVertically(int fieldsToMove) {
    const Direction newDirection = fieldsToMove > 0 ? SOUTH : NORTH;

    // turn in the right direction if necessary
    switch (currentDirection) {
        case NORTH:
            if (newDirection == SOUTH) {
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            }
            break;
        case EAST:
            newDirection == SOUTH ?  ecpMovement.turnRight() : ecpMovement.turnLeft();
            break;
        case SOUTH:
            if (newDirection != SOUTH) {
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            }
            break;
        case WEST:
            newDirection == SOUTH ? ecpMovement.turnLeft() : ecpMovement.turnRight();
    }

    currentDirection = newDirection;
    ecpMovement.move(abs(fieldsToMove));
};

void ECPChessPiece::turnBackToInitialDirection() {
    switch (currentDirection) {
        case NORTH:
            if (isWhite) {
                // already facing in correct direction
            } else {
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            }
            break;
        case EAST:
            isWhite ? ecpMovement.turnLeft() : ecpMovement.turnRight();
            break;
        case SOUTH:
            if (isWhite) {
                ecpMovement.turnLeft();
                ecpMovement.turnLeft();
            } else {
                // already facing in correct direction
            }
            break;
        case WEST:
            isWhite ? ecpMovement.turnRight() : ecpMovement.turnLeft();
    }

    currentDirection = isWhite ? NORTH : SOUTH;
};

void ECPChessPiece::setRedLight(bool shouldEnable) {
    if (shouldEnable) {
        const uint32_t red = dezibot.multiColorLight.color(100, 0, 0);
        dezibot.multiColorLight.setLed(BOTTOM, red);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};

void ECPChessPiece::setGreenLight(bool shouldEnable) {
    if (shouldEnable) {
        const uint32_t green = dezibot.multiColorLight.color(0, 100, 0);
        dezibot.multiColorLight.setLed(BOTTOM, green);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};
