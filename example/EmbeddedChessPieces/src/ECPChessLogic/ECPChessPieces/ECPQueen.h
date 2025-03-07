/**
 * @file ECPQueen.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Queen chess piece implementation
 * @version 0.1
 * @date 2024-12-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPQueen_h
#define ECPQueen_h

#include "../ECPChessPiece.h"

class ECPQueen : public ECPChessPiece {
public:
     /**
     * @brief Construct a new Queen chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param ecpMovement Movement object of dezibot
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPQueen(
        Dezibot &d,
        ECPMovement &ecpMovement,
        ECPChessField initialField,
        bool isWhite
    );

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @attention Note that if it is always assumed, that leaping over other
     *            pieces is not required.
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
    void drawFigureToDisplay() const override;
};

#endif // ECPQueen_h
