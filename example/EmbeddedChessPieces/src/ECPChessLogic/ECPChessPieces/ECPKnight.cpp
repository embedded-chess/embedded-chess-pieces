#include "ECPKnight.h"

ECPKnight::ECPKnight(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : ECPChessPiece(d, ecpMovement, initialField, isWhite) {};

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

void ECPKnight::drawFigureToDisplay() const {
    dezibot.display.clear();
    
    dezibot.display.println(" _   \\\\\\\\\\\\\\    ");
    dezibot.display.println("| n___\\\\\\\\\\\\\\   ");
    dezibot.display.println("| |     \\\\\\\\\\>  ");
    dezibot.display.println("| |          |> ");
    dezibot.display.println("| |_____|  @ |  ");
    dezibot.display.println("|_u     )   /   ");
    dezibot.display.println("       (   /    ");
    dezibot.display.println("       `__/     ");
}
