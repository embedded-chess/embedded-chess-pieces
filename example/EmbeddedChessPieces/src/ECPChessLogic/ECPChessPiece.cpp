#include "ECPChessPiece.h"

ECPChessPiece::ECPChessPiece(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : dezibot(d),
    ecpMovement(ecpMovement),
    currentField(initialField),
    isWhite(isWhite) {};

bool ECPChessPiece::move(ECPChessField newField) {
    if (!isMoveValid(newField)) {
        setRedLight(true);
        delay(COLOR_DELAY);
        setRedLight(false);
        return false;
    }

    const int colDiff = currentField.column - newField.column;
    const int rowDiff = currentField.row - newField.row;

    // move horizontally
    if (colDiff != 0) {
        const int fieldsToMove = abs(colDiff);
        const bool mustTurnLeft = isWhite ? colDiff > 0 : colDiff < 0;

        moveHorizontally(fieldsToMove, mustTurnLeft);
    }

    // move vertically
    if (rowDiff != 0) {
        const int fieldsToMove = abs(rowDiff);
        const bool mustTurn = isWhite ? rowDiff > 0 : rowDiff > 0;

        moveVertically(fieldsToMove, mustTurn);
    }

    currentField = newField;

    // show green validation light
    setGreenLight(true);
    delay(COLOR_DELAY);
    setGreenLight(false);

    return true;
};

ECPChessField ECPChessPiece::getCurrentField() {
    return currentField;
};

void ECPChessPiece::moveHorizontally(uint fieldsToMove, bool mustTurnLeft) {
    // turn in the right direction
    mustTurnLeft ? ecpMovement.turnLeft() : ecpMovement.turnRight();

    // move dezibot on the chess board
    ecpMovement.move(fieldsToMove);

    // turn back
    mustTurnLeft ? ecpMovement.turnRight() : ecpMovement.turnLeft();
};

void ECPChessPiece::moveVertically(uint fieldsToMove, bool mustTurn) {
    // turn dezibot if necessary
    if (mustTurn) {
        ecpMovement.turnLeft();
        ecpMovement.turnLeft();
    }

    // move dezibot on the chess board
    ecpMovement.move(fieldsToMove);

    // turn back to initial direction
    if (mustTurn) {
        ecpMovement.turnLeft();
        ecpMovement.turnLeft();
    }
};

void ECPChessPiece::setRedLight(bool shouldEnable) {
    if (shouldEnable) {
        // TODO: select nicer colour
        const uint32_t red = dezibot.multiColorLight.color(100, 0, 0);
        dezibot.multiColorLight.setLed(BOTTOM, red);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};

void ECPChessPiece::setGreenLight(bool shouldEnable) {
    if (shouldEnable) {
        // TODO: select nicer colour
        const uint32_t green = dezibot.multiColorLight.color(0, 100, 0);
        dezibot.multiColorLight.setLed(BOTTOM, green);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};
