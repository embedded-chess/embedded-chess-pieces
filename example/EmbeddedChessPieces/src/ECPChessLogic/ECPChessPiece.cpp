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
        return false;
    }

    // TODO: #4 implement actual movement on board

    currentField = newField;
    return true;
};

ECPChessField ECPChessPiece::getCurrentField() {
    return currentField;
};
