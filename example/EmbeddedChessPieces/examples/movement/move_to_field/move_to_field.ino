/**
 * @file move_to_field.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example for moving chess piece on the board
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

#define BAUD_RATE 9600

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement = ECPMovement(dezibot);

void setup() {
    Serial.begin(BAUD_RATE);
    dezibot.begin();
    delay(500);
    
    dezibot.display.flipOrientation();

    // color sensor
    // ecpMovement.setShouldTurnOnColorCorrectionLight(true);
    // ecpMovement.calibrateFieldColor();

    // infrared
    ecpMovement.setColorDetectionMode(true);
    ecpMovement.calibrateIRFieldColor();
}

void loop() {
    iteration(true);
    iteration(false);
}

void iteration(bool isWhite) {
    dezibot.display.clear();
    const String color = isWhite ? "white" : "black";
    dezibot.display.println("Prepare " + color +  "\nYou've got \n10 seconds...");
    delay(10000);

    const String prefix = isWhite ? "White" : "Black";
    dezibot.display.println(prefix + " queen...");
    moveQueen(isWhite);
}

void moveQueen(bool isWhite) {
    const ECPChessField initialField = { D, 4 };
    ECPQueen queen = ECPQueen(dezibot, ecpMovement, initialField, isWhite);

    /*
         ABCDEFGH
        7
        6   X
        5   ↑↘
        4   I←X
        3
    */
    const ECPChessField fields[] = {
        { D, 6 }, { F, 4 }, { F, 4 }, initialField
    };

    dezibot.display.clear();
    dezibot.display.print(initialField.toString() + " -> ");
    for (const ECPChessField field : fields) {
        dezibot.display.println(field.toString());
        delay(3000);

        queen.drawFigureToDisplay();
        queen.move(field);

        dezibot.display.clear();
        dezibot.display.print(field.toString() + " -> ");
    }
}
