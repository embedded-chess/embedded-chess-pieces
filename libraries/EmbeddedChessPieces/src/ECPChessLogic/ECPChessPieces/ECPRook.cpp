#include "ECPRook.h"

ECPRook::ECPRook(Dezibot &d, ECPChessField initialField, bool isWhite)
    : ECPChessPiece(d, initialField, isWhite) {};

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
