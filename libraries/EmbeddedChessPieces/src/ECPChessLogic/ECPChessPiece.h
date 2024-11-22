/**
 * @file ChessPiece.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Chess piece class
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPChessPiece_h
#define ECPChessPiece_h

#include <Dezibot.h>
#include "ECPChessField.h"

/**
 * @brief Abstract class for chess piece, e.g. pawn, tower etc.
 * 
 */
class ECPChessPiece {
public:
    const Dezibot& dezibot;

    /**
     * @brief Construct a new chess piece object
     * 
     * @param d Dezibot that simulates the piece
     * @param initialField Initial field of chess piece on board, i.e. A1 white tower
     */
    ECPChessPiece(Dezibot &d, ECPChessField initialField, bool isWhite);

    /**
     * @brief Determine if move from current field to passed new field is valid
     *        for this chess piece.
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    virtual bool isMoveValid(ECPChessField newField) = 0;

    /**
     * @brief Move to new field if valid
     * 
     * @param newField New field on which to move
     * @return true if move is valid
     * @return false otherwise
     */
    bool move(ECPChessField newField);

    /**
     * @brief Get the current field
     * 
     * @return ECPChessField current field
     */
    ECPChessField getCurrentField();

    /**
     * @brief True if chess piece is white, false if black
     * 
     */
    const bool isWhite;

protected:
    /**
     * @brief Current field of chess piece
     * 
     */
    ECPChessField currentField;
};

#endif // ECPChessPiece_h
