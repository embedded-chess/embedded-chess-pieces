/**
 * @file embedded_chess_piece.ino
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
ECPMovement ecpMovement = ECPMovement(dezibot);

void setup() {
    dezibot.begin();
    delay(100);

    // use IR based approach for field color detection
    ecpMovement.setUseInfraredColorDetection(true);
    ecpMovement.calibrateIRFieldColor();

    moveWhitePawn();
    delay(5000);

    blackQueen();
    delay(5000);

    dezibot.display.println("Done");
}

void loop() {}

/**
 * @brief Let dezibot simulate a white pawn and do valid and invalid movements.
 * 
 */
void moveWhitePawn() {
    const ECPChessField initialField = { E, 2 };

    const String request = "Position to\n> " + initialField.toString() + " NORTH";
    dezibot.display.println(request);
    delay(3000);

    ECPPawn pawn = ECPPawn(dezibot, ecpMovement, initialField, true);

    const ECPChessField fields[] = {{ E, 4 }, { E, 6 }, { E, 5 }};
    for (const ECPChessField field : fields) {
        pawn.move(field);
        delay(2000);
    }
}

/**
 * @brief Let dezibot simulate a black queen and do valid and invalid movements.
 * 
 */
void blackQueen() {
    const ECPChessField initialField = { E, 8 };

    const String request = "Position to\n> " + initialField.toString() + " SOUTH";
    dezibot.display.println(request);
    delay(3000);

    ECPQueen queen = ECPQueen(dezibot, ecpMovement, initialField, false);

    const ECPChessField fields[] = {{ G, 6 }, { F, 4 }, { G, 8 }};
    for (const ECPChessField field : fields) {
        queen.move(field);
        delay(2000);
    }
}
