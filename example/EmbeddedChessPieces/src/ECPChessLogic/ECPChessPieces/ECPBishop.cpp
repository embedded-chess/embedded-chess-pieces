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

void ECPBishop::drawFigureToDisplay() {
    dezibot.display.clear();
    
    dezibot.display.println(" _        __    ");
    dezibot.display.println("| n_____ /  \\   ");
    dezibot.display.println("| |     ||   \\  ");
    dezibot.display.println("| |     ||  + |O");
    dezibot.display.println("| |_____||   /  ");
    dezibot.display.println("|_u      \\__/   ");
    dezibot.display.println("                ");
    dezibot.display.println("                ");
}
