/**
 * @file pawn_move_validation_test.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test for ECPPawn isMoveValid method.
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

#define BAUD_RATE 9600

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(BAUD_RATE);
    dezibot.begin();
    delay(1000);

    testWhitePawn();
    Serial.println();
    testBlackPawn();
}

void loop() { }

void testWhitePawn() {
    ECPChessField initialField = { A, 2 };
    ECPPawn pawn = ECPPawn(dezibot, initialField, true);

    // valid moves
    test(pawn.isMoveValid({ A, 3 }), true, "A3");
    test(pawn.isMoveValid({ A, 4 }), true, "A4");

    // valid move assuming that there is an opponent to capture
    test(pawn.isMoveValid({ B, 3 }), true, "B3");
    
    // invalid moves
    test(pawn.isMoveValid({ A, 1 }), false, "A1");
    test(pawn.isMoveValid({ A, 5 }), false, "A4");
    test(pawn.isMoveValid({ B, 2 }), false, "B2");
    test(pawn.isMoveValid({ B, 1 }), false, "B1");
}

void testBlackPawn() {
    ECPChessField initialField = { C, 7 };
    ECPPawn pawn = ECPPawn(dezibot, initialField, false);

    // valid moves
    test(pawn.isMoveValid({ C, 6 }), true, "C6");
    test(pawn.isMoveValid({ C, 5 }), true, "C5");

    // valid move assuming that there is an opponent to capture
    test(pawn.isMoveValid({ D, 6 }), true, "D6");
    
    // invalid moves
    test(pawn.isMoveValid({ C, 1 }), false, "C1");
    test(pawn.isMoveValid({ C, 4 }), false, "C4");
    test(pawn.isMoveValid({ B, 7 }), false, "B7");
    test(pawn.isMoveValid({ D, 8 }), false, "D8");
}

void test(bool actual, bool expected, String field) {
    if (actual == expected) {
        Serial.print("Correct for ");
        Serial.println(field);
    } else {
        Serial.print("Wrong for ");
        Serial.println(field);
    }
    delay(500);
}
