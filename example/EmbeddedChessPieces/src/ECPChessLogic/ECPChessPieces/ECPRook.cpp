#include "ECPRook.h"

ECPRook::ECPRook(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : ECPChessPiece(d, ecpMovement, initialField, isWhite) {};

bool ECPRook::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // rook must move
        return false;
    }

    const bool doesChangeColumn = currentField.column != newField.column;
    const bool doesChangeRow = currentField.row != newField.row;

    if (doesChangeColumn != doesChangeRow) {
        // moves horizontally but not vertically or vice versa
        return true;
    }

    return false;
};

void ECPRook::drawFigureToDisplay() {
    dezibot.display.clear();
    
    dezibot.display.println(" __        ___  ");
    dezibot.display.println("|  n____ _/   | ");
    dezibot.display.println("|  |    #   |=  ");
    dezibot.display.println("|  |    #     | ");
    dezibot.display.println("|  |    #   |=  ");
    dezibot.display.println("|  |    #     | ");
    dezibot.display.println("|  |____#_  |=  ");
    dezibot.display.println("|__u      \\___| ");
}
