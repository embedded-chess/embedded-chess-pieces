#include "ECPBishop.h"

ECPBishop::ECPBishop(Dezibot &d, ECPChessField initialField, bool isWhite)
    : ECPChessPiece(d, initialField, isWhite) {};

bool ECPBishop::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // rook must move
        return false;
    }

    const int columnDiff = newField.column - currentField.column;
    const int rowDiff = newField.row - currentField.row;

    if (abs(columnDiff) == abs(rowDiff)) {
        return true;
    }

    return false;
};
