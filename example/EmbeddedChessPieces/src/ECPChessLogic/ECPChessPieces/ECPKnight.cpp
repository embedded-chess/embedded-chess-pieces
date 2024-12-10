#include "ECPKnight.h"

ECPKnight::ECPKnight(Dezibot &d, ECPChessField initialField, bool isWhite)
    : ECPChessPiece(d, initialField, isWhite) {};

bool ECPKnight::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // knight must move
        return false;
    }

    const int columnDiff = abs((int) newField.column - (int) currentField.column);
    const int rowDiff = abs((int) newField.row - (int) currentField.row);

    // move forms an "L"-shape

    if (columnDiff == 2 && rowDiff == 1) {
        // two field horizontally and one vertically
        return true;
    }
    if (columnDiff == 1 && rowDiff == 2) {
        // two fields vertically and one horizontally
        return true;
    }
    
    return false;
};
