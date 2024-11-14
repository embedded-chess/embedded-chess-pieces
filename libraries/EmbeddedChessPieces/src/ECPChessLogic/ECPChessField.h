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

/**
 * @brief Enumeration for column of chess board
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
    ECPBoardColumn column;
    unsigned int row;

    bool operator==(const ECPChessField& rhs) const {
        return column == rhs.column && row == rhs.row;
    }
};

#endif // ECPChessField_h
