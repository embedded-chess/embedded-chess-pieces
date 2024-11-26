/**
 * @file ECPKnight.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Knight chess piece implementation
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPKnight_h
#define ECPKnight_h

#include "../ECPChessPiece.h"

class ECPKnight : public ECPChessPiece {
public:
    /**
     * @brief Construct a new Knight chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPKnight(Dezibot &d, ECPChessField initialField, bool isWhite);

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    bool isMoveValid(ECPChessField newField);
};

#endif // ECPKnight_h
