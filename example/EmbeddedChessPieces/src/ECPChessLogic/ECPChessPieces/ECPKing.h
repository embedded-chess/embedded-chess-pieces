/**
 * @file ECPKing.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief King chess piece implementation.
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPKing_h
#define ECPKing_h

#include "../ECPChessPiece.h"

class ECPKing : public ECPChessPiece {
public:
    /**
     * @brief Construct a new King chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPKing(Dezibot &d, ECPChessField initialField, bool isWhite);

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    bool isMoveValid(ECPChessField newField) override;
};

#endif // ECPKing_h
