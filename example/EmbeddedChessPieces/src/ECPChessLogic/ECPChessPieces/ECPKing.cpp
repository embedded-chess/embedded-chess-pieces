#include "ECPKing.h"

ECPKing::ECPKing(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : ECPChessPiece(d, ecpMovement, initialField, isWhite) {};

bool ECPKing::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // king must move
        return false;
    }

    const int columnDiff = newField.column - currentField.column;
    const int rowDiff = newField.row - currentField.row;

    if (abs(columnDiff) <= 1 && abs(rowDiff) <= 1) {
        return true;
    }
    
    return false;
};

void ECPKing::drawFigureToDisplay() const {
    dezibot.display.clear();
    
    dezibot.display.println(" __        __   ");
    dezibot.display.println("|  n____  /  \\  ");
    dezibot.display.println("|  |    |#   /  ");
    dezibot.display.println("|  |    |#   \\  ");
    dezibot.display.println("|  |    |#    )+");
    dezibot.display.println("|  |    |#   /  ");
    dezibot.display.println("|  |____|#   \\  ");
    dezibot.display.println("|__u      \\__/  ");
}
