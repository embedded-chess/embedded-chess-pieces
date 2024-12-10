#include "ECPQueen.h"

ECPQueen::ECPQueen(Dezibot &d, ECPChessField initialField, bool isWhite)
    : ECPChessPiece(d, initialField, isWhite) {};

bool ECPQueen::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // queen must move
        return false;
    }

    const int columnDiff = newField.column - currentField.column;
    const int rowDiff = newField.row - currentField.row;

    if (abs(columnDiff) == abs(rowDiff)) {
        // Bishop behavior: moving diagonally
        return true;
    }

    if (columnDiff == 0 || rowDiff == 0) {
        // Rook behavior: moving horizontally but not vertically or vice versa
        return true;
    }

    return false;
};
