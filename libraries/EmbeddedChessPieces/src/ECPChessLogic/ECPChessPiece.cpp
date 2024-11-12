#include "ECPChessPiece.h"

ECPChessPiece::ECPChessPiece(Dezibot &d, ECPChessField initialField)
    : dezibot(d), currentField(initialField) {
    // row 1 and 2 are white, 7 and 8 black
    isWhite = initialField.row <= 2;
};

ECPChessField ECPChessPiece::getCurrentField() {
    return currentField;
};
