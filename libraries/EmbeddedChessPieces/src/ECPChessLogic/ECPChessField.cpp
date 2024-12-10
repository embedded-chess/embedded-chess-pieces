#include "ECPChessField.h"

ECPChessField::ECPChessField(ECPBoardColumn column,
                             unsigned int row) : column(column), row(row) {
    if (row < 1 || row > 8) {
        throw std::runtime_error("Row must be valid, i.e. in [1, 8]");
    }
};

String ECPChessField::toString() const {
    char columnChar = 'A' + column;
    String result = String(columnChar) + String(row);
    return result;
};

bool ECPChessField::operator==(const ECPChessField& rhs) const {
    return column == rhs.column && row == rhs.row;
};
