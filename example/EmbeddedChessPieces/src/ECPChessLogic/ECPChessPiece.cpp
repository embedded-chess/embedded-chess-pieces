#include "ECPChessPiece.h"

ECPChessPiece::ECPChessPiece(Dezibot &d, ECPChessField initialField, bool isWhite)
    : dezibot(d), currentField(initialField), isWhite(isWhite) {};

bool ECPChessPiece::move(ECPChessField newField) {
    if (!isMoveValid(newField)) {
        return false;
    }

    // TODO: #4 implement actual movement on board

    currentField = newField;
    return true;
};

ECPChessField ECPChessPiece::getCurrentField() {
    return currentField;
};
