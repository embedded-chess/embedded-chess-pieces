/**
 * @file playground.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Showcase of Embedded Chess Pieces
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>

Dezibot dezibot = Dezibot();

void setup() {
    dezibot.begin();
    delay(100);

    // TODO: calibrate

    moveChessPiece();
    dezibot.display.println("Done");
}

void loop() {}

void moveChessPiece() {
    // provide initial field for chess piece
    const ECPChessField initialField = { E, 2 };

    // select whether piece shall be white (true) or black (false)
    const bool isWhitePiece = true;

    // print request to user to position 
    const String request = "Position to\n> " + initialField.toString()
        + isWhitePiece ? " NORTH" : "SOUTH";
    dezibot.display.println(request);
    delay(5000);

    // optionally, adjust movement calibration factor for dezibot
    const uint movementCalibration = DEFAULT_MOVEMENT_CALIBRATION;
    ECPMovement ecpMovement = ECPMovement(dezibot, movementCalibration);

    // select chess piece type, i.e. Bishop, King, Knight, Pawn, Queen, Rook
    // ECP<TYPE> chessPiece = ECP<TYPE>(...);
    ECPPawn chessPiece = ECPPawn(dezibot, ecpMovement, initialField, isWhitePiece);

    // add fields to which the dezibot shall move
    const ECPChessField fields[] = {{ E, 4 }, { E, 6 }, { E, 5 }};

    // move chess piece to selected fields
    // note that LED will indicate if move is valid
    for (const ECPChessField field : fields) {
        chessPiece.move(field);
        delay(3000);
    }
}
