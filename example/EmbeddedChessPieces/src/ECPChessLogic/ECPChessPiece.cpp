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
    currentDirection(isWhite ? NORTH : SOUTH) {
        if (isWhite != d.display.getColorInverted()) {
            d.display.invertColor();
        }
    };

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
    const ECPDirection newDirection = fieldsToMove > 0 ? WEST : EAST;

    // turn in the right direction if necessary
    switch (currentDirection) {
        case NORTH:
            if (newDirection == WEST) {
                ecpMovement.turnLeft(currentField, WEST);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnRight(currentField, EAST);
                drawFigureToDisplay();
            }
            break;
        case EAST:
            if (newDirection == WEST) {
                ecpMovement.turnLeft(currentField, NORTH);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, WEST);
                drawFigureToDisplay();
            }
            break;
        case SOUTH:
            if (newDirection == WEST) {
                ecpMovement.turnRight(currentField, WEST);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnLeft(currentField, EAST);
                drawFigureToDisplay();
            }
            break;
        case WEST:
            if (newDirection == EAST) {
                // turn around
                ecpMovement.turnLeft(currentField, SOUTH);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, EAST);
                drawFigureToDisplay();
            }
    }

    currentDirection = newDirection;
    ecpMovement.move(abs(fieldsToMove));
};

void ECPChessPiece::moveVertically(int fieldsToMove) {
    const ECPDirection newDirection = fieldsToMove > 0 ? SOUTH : NORTH;

    // turn in the right direction if necessary
    switch (currentDirection) {
        case NORTH:
            if (newDirection == SOUTH) {
                ecpMovement.turnLeft(currentField, WEST);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, SOUTH);
                drawFigureToDisplay();
            }
            break;
        case EAST:
            if (newDirection == SOUTH) {
                ecpMovement.turnRight(currentField, SOUTH);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnLeft(currentField, NORTH);
                drawFigureToDisplay();
            }
            break;
        case SOUTH:
            if (newDirection == NORTH) {
                ecpMovement.turnLeft(currentField, EAST);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, NORTH);
                drawFigureToDisplay();
            }
            break;
        case WEST:
            if (newDirection == SOUTH) {
                ecpMovement.turnLeft(currentField, SOUTH);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnRight(currentField, NORTH);
                drawFigureToDisplay();
            }
    }

    currentDirection = newDirection;
    ecpMovement.move(abs(fieldsToMove));
};

void ECPChessPiece::turnBackToInitialDirection() {
    switch (currentDirection) {
        case NORTH:
            if (!isWhite) {
                ecpMovement.turnLeft(currentField, WEST);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, SOUTH);
                drawFigureToDisplay();
            }
            break;
        case EAST:
            if (isWhite) {
                ecpMovement.turnLeft(currentField, NORTH);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnRight(currentField, SOUTH);
                drawFigureToDisplay();
            }
            break;
        case SOUTH:
            if (isWhite) {
                ecpMovement.turnLeft(currentField, EAST);
                drawFigureToDisplay();
                ecpMovement.turnLeft(currentField, NORTH);
                drawFigureToDisplay();
            }
            break;
        case WEST:
            if (isWhite) {
                ecpMovement.turnRight(currentField, NORTH);
                drawFigureToDisplay();
            } else {
                ecpMovement.turnLeft(currentField, SOUTH);
                drawFigureToDisplay();
            }
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
