/**
 * @file playground.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Playground for Embedded Chess Pieces
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>

// optionally, adjust movement calibration factor for dezibot
const uint movementCalibration = DEFAULT_MOVEMENT_CALIBRATION;

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement = ECPMovement(dezibot, movementCalibration);

void setup() {
    dezibot.begin();
    delay(100);

    // select whether to use IR or RGB for detecting field colors
    const bool useInfraredColorDetection = true;
    calibrate(useInfraredColorDetection);

    moveChessPiece();
    dezibot.display.println("Done");
}

void loop() {}

/**
 * @brief Calibrate dezibot color detection of field colors.
 * 
 * @param useIR true for using IR based approach,
 *              false for using RGB based approach
 */
void calibrate(bool useIR) {
    if (useIR) {
        ecpMovement.setUseInfraredColorDetection(true);
        ecpMovement.calibrateIRFieldColor();
    } else {
        ecpMovement.setShouldTurnOnColorCorrectionLight(true);
        ecpMovement.calibrateFieldColor();
    }
}

/**
 * @brief Create chess piece and move to various fields.
 * 
 * Here the chess piece type and color, as well initial field and fields where
 * the dezibot shall move can be specified.
 * 
 */
void moveChessPiece() {
    // provide initial field for chess piece
    const ECPChessField initialField = { E, 2 };

    // select whether piece shall be white (true) or black (false)
    const bool isWhitePiece = true;

    // print request to user to position 
    const String request = "Position to\n> " + initialField.toString()
        + (isWhitePiece ? " NORTH" : "SOUTH");
    dezibot.display.println(request);
    delay(5000);

    // select chess piece type, i.e. Bishop, King, Knight, Pawn, Queen, Rook
    // ECP<TYPE> chessPiece = ECP<TYPE>(...);
    ECPPawn chessPiece = ECPPawn(dezibot, ecpMovement, initialField, isWhitePiece);

    // add fields to which the dezibot shall move
    const ECPChessField fields[] = {{ E, 4 }, { E, 6 }, { E, 5 }};

    // move chess piece to selected fields
    // note that dezibot will only move if the provided move is valid
    // valid move will be indicated by green, invalid by red light
    for (const ECPChessField field : fields) {
        chessPiece.move(field);
        delay(3000);
    }
    dezibot.display.clear();
}
