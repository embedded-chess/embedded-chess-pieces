#include "ECPBishop.h"

ECPBishop::ECPBishop(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : ECPChessPiece(d, ecpMovement, initialField, isWhite) {};

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
