/**
 * @file ECPChessField.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper classes for chess field
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPChessField_h
#define ECPChessField_h

#include <Arduino.h>

/**
 * @brief Enumeration for column of chess board.
 * 
 * Convertible to int reaching from 0 to 7, i.e. A == 0, B == 1, etc.
 * 
 */
enum ECPBoardColumn {
    A, B, C, D, E, F, G, H
};

/**
 * @brief Structure representing one field on a chess board.
 * 
 */
struct ECPChessField {

    /**
     * @brief Column of the field, i.e. "B" in field "B1".
     * 
     */
    ECPBoardColumn column;

    /**
     * @brief Row of the field, i.e. "1" in "B1".
     * 
     * @attention Must be between 1 and 8. Otherwise, a runtime exception will
     *            be thrown.
     * 
     */
    unsigned int row;

    ECPChessField(ECPBoardColumn column, unsigned int row);

    String toString() const;

    bool operator==(const ECPChessField& rhs) const;
    bool operator!=(const ECPChessField& rhs) const;
};

#endif // ECPChessField_h
