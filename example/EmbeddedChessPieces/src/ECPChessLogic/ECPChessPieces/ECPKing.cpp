#include "ECPKing.h"

ECPKing::ECPKing(Dezibot &d, ECPChessField initialField, bool isWhite)
    : ECPChessPiece(d, initialField, isWhite) {};

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
