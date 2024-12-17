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

void ECPChessPiece::setRedLight(bool shouldEnable) {
    if (shouldEnable) {
        // TODO: select nicer colour
        const uint32_t red = dezibot.multiColorLight.color(100, 0, 0);
        dezibot.multiColorLight.setLed(BOTTOM, red);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};

void ECPChessPiece::setGreenLight(bool shouldEnable) {
    if (shouldEnable) {
        // TODO: select nicer colour
        const uint32_t green = dezibot.multiColorLight.color(0, 100, 0);
        dezibot.multiColorLight.setLed(BOTTOM, green);
    } else {
        dezibot.multiColorLight.turnOffLed(BOTTOM);
    }
};
