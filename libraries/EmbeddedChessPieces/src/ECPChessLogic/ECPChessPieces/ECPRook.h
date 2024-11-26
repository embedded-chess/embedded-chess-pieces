/**
 * @file ECPRook.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Rook chess piece implementation
 * @version 0.1
 * @date 2024-11-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPRook_h
#define ECPRook_h

#include "../ECPChessPiece.h"

class ECPRook : public ECPChessPiece {
public:
    /**
     * @brief Construct a new Rook chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPRook(Dezibot &d, ECPChessField initialField, bool isWhite);

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @attention Note that if it is always assumed, that leaping over other
     *            pieces is not required. Also, castling is not implemented.
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    bool isMoveValid(ECPChessField newField);
};

#endif // ECPRook_h
