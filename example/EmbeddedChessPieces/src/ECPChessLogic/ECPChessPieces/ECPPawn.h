/**
 * @file ECPPawn.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Pawn chess piece implementation.
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPPawn_h
#define ECPPawn_h

#include "../ECPChessPiece.h"

class ECPPawn : public ECPChessPiece {
public:
    /**
     * @brief Construct a new chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param ecpMovement Movement object of dezibot
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPPawn(
        Dezibot &d,
        ECPMovement &ecpMovement,
        ECPChessField initialField,
        bool isWhite
    );

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @attention Note that if the pawn moves one field diagonally, it is
     *            assumed that there is an opponent to capture.
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    bool isMoveValid(ECPChessField newField) override;
    
    /**
     * @brief Print chess piece display-representation to the display
     * 
     */
    void drawFigureToDisplay() override;

private:
    /**
     * @brief Initial row of white pawns
     * 
     * @attention This value is **not** adjusted for array indexing!
     */
    const int INITIAL_ROW_WHITE = 2;

    /**
     * @brief Initial row of black pawns
     * 
     * @attention This value is **not** adjusted for array indexing!
     */
    const int INITIAL_ROW_BLACK = 7;
};

#endif // ECPPawn_h
