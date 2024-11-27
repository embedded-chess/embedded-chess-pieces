/**
 * @file ECPBishop.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Bishop chess piece implementation
 * @version 0.1
 * @date 2024-11-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPBishop_h
#define ECPBishop_h

#include "../ECPChessPiece.h"

class ECPBishop : public ECPChessPiece {
public:
    /**
     * @brief Construct a new Bishop chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPBishop(Dezibot &d, ECPChessField initialField, bool isWhite);

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

#endif // ECPBishop_h
