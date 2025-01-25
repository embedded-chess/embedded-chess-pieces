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
#include "ECPMovement/ECPMovement.h"


#define COLOR_DELAY 2000

/**
 * @brief Abstract class for chess piece, e.g. pawn, tower etc.
 * 
 */
class ECPChessPiece {
public:
    Dezibot& dezibot;

    /**
     * @brief Construct a new chess piece object
     * 
     * Invert the color of the display if chess piece is white
     * 
     * @param d Dezibot that simulates the piece
     * @param ecpMovement Movement object of dezibot
     * @param initialField Initial field of chess piece on board
     * @param isWhite True if piece is white, false if black
     */
    ECPChessPiece(
        Dezibot &d,
        ECPMovement &ecpMovement,
        ECPChessField initialField,
        bool isWhite
    );

    /**
     * @brief Relative direction in which the chess piece is facing.
     * 
     * - North means that the Dezibot is facing in the direction of increasing
     *   row numbers, i.e. 1,2,3,...
     * - East means that the Dezibot is facing in the direction of increasing
     *   column numbers, i.e. A,B,C,...
     * - South means that the Dezibot is facing in the direction of decreasing
     *   row numbers, i.e. 8,7,6,...
     * - West means that the Dezibot is facing in the direction of decreasing
     *   column numbers, i.e. H,G,F,...
     * 
     */
    enum Direction {
        NORTH, EAST, SOUTH, WEST
    };

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
     * @brief Move to new field if valid.
     * 
     * Dezibot will always face forward *before* and *after* moving, i.e. black
     * pieces will always face south and white pieces will always face north.
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

    /**
     * @brief Print chess piece display-representation to the display
     * 
     */
    virtual void drawFigureToDisplay() = 0;

protected:
    /**
     * @brief Current field of chess piece
     * 
     */
    ECPChessField currentField;

private:
    /**
     * @brief Strings to draw the chess piece
     *  
     */
    const String[] displayRepresentation;

};

#endif // ECPChessPiece_h
