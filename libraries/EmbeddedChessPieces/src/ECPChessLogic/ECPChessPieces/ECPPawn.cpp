#include "ECPPawn.h"

ECPPawn::ECPPawn(Dezibot &d, ECPChessField initialField) : ECPChessPiece(d, initialField) {
    // row 1 and 2 are white, 7 and 8 black
    isWhite = initialField.row <= 2;
};

bool ECPPawn::isMoveValid(ECPChessField newField) {
    const bool doesNotChangeColumn = currentField.column == newField.column;
    const int rowDiff = currentField.row - newField.row;
    const bool isMoveOneHorizontally = abs(currentField.column - newField.column) == 1;

    if (isWhite) {
        if (doesNotChangeColumn && rowDiff == 1) {
            // pawn draws one field forward
            return true;
        }

        const bool isOnInitialRow = currentField.row == INITIAL_ROW_WHITE - 1;
        const int isNewRowTwoBeforeInitial = newField.row == INITIAL_ROW_WHITE + 2 - 1;

        if (doesNotChangeColumn && isOnInitialRow && isNewRowTwoBeforeInitial) {
            // pawn did not move yet, enters with two field move forward
            return true;
        }
        if (isMoveOneHorizontally && rowDiff == 1) {
            // pawn is capturing, moves diagonally
            return true;
        }
    } else {
        if (doesNotChangeColumn && rowDiff == -1) {
            // pawn draws one field forward
            return true;
        }

        const bool isOnInitialRow = currentField.row == INITIAL_ROW_BLACK - 1;
        const int isNewRowTwoBeforeInitial = newField.row == INITIAL_ROW_BLACK - 2 - 1;

        if (doesNotChangeColumn && isOnInitialRow && isNewRowTwoBeforeInitial) {
            // pawn did not move yet, enters with two field move forward
            return true;
        }
        if (isMoveOneHorizontally && rowDiff == -1) {
            // pawn is capturing, moves diagonally
            return true;
        }
    }

    return false;
};
