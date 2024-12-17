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


#define COLOR_DELAY 1000

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
     * @param d Dezibot that simulates the piece
     * @param ecpMovement Movement object of dezibot
     * @param initialField Initial field of chess piece on board, i.e. A1 white tower
     * @param isWhite True if piece is white, false if black
     */
    ECPChessPiece(
        Dezibot &d,
        ECPMovement &ecpMovement,
        ECPChessField initialField,
        bool isWhite
    );

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

protected:
    /**
     * @brief Current field of chess piece
     * 
     */
    ECPChessField currentField;

    ECPMovement& ecpMovement;

private:
    /**
     * @brief Move dezibot horizontally for the passed number of fields.
     * 
     * @param fieldsToMove number of fields the dezibot needs to move
     * @param mustTurnLeft true if dezibot needs to turn left, turn right otherwise
     */
    void moveHorizontally(uint fieldsToMove, bool mustTurnLeft);

    /**
     * @brief Move dezibot vertically for the passed number of fields.
     * 
     * @param fieldsToMove number of fields the dezibot needs to move.
     * @param mustTurn true if dezibot needs to turn 180°, will not turn otherwise
     */
    void moveVertically(uint fieldsToMove, bool mustTurn);

    /**
     * @brief Turn the red light of the dezibot on or off.
     * 
     * @param shouldEnable if true turn on, otherwise turn off
     */
    void setRedLight(bool shouldEnable);

    /**
     * @brief Turn the green light of the dezibot on or off.
     * 
     * @param shouldEnable if true turn on, otherwise turn off
     */
    void setGreenLight(bool shouldEnable);
};

#endif // ECPChessPiece_h
