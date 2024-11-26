/**
 * @file rook.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test for ECPRook isMoveValid method.
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
    delay(500);
}

void loop() {
    Serial.println("\n=== STARTING TEST ===\n");

    Serial.println("Testing rook on initial field...");
    testRookOnInitialField();
    Serial.println("\nTesting rook in board center...");
    testRookInBoardCenter();

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}

void testRookOnInitialField() {
    const ECPChessField initialField = { A, 1 };
    ECPRook rook = ECPRook(dezibot, initialField, true);

    // valid moves
    test(rook.isMoveValid({ A, 2 }), true, "A2");
    test(rook.isMoveValid({ A, 8 }), true, "A8");
    test(rook.isMoveValid({ B, 1 }), true, "B1");
    test(rook.isMoveValid({ H, 1 }), true, "H1");

    // invalid moves
    test(rook.isMoveValid(initialField), false, "A1");
    test(rook.isMoveValid({ B, 4 }), false, "B2");
    test(rook.isMoveValid({ B, 8 }), false, "B8");
    test(rook.isMoveValid({ H, 8 }), false, "H8");
}

void testRookInBoardCenter() {
    const ECPChessField initialField = { D, 5 };
    ECPRook rook = ECPRook(dezibot, initialField, false);

    // valid moves - horizontally
    test(rook.isMoveValid({ A, 5 }), true, "A5");
    test(rook.isMoveValid({ B, 5 }), true, "B5");
    test(rook.isMoveValid({ C, 5 }), true, "C5");
    test(rook.isMoveValid({ E, 5 }), true, "E5");
    test(rook.isMoveValid({ F, 5 }), true, "F5");
    test(rook.isMoveValid({ G, 5 }), true, "G5");
    test(rook.isMoveValid({ H, 5 }), true, "H5");

    // valid moves - vertically
    test(rook.isMoveValid({ D, 1 }), true, "D1");
    test(rook.isMoveValid({ D, 2 }), true, "D2");
    test(rook.isMoveValid({ D, 3 }), true, "D3");
    test(rook.isMoveValid({ D, 4 }), true, "D4");
    test(rook.isMoveValid({ D, 6 }), true, "D6");
    test(rook.isMoveValid({ D, 7 }), true, "D7");
    test(rook.isMoveValid({ D, 8 }), true, "D8");

    // invalid moves
    test(rook.isMoveValid({ D, 5 }), false, "D5");
    test(rook.isMoveValid({ C, 4 }), false, "C4");
    test(rook.isMoveValid({ C, 6 }), false, "C6");
    test(rook.isMoveValid({ E, 6 }), false, "E6");
    test(rook.isMoveValid({ E, 4 }), false, "E4");
}

void test(bool actual, bool expected, String field) {
    if (actual == expected) {
        Serial.print(field);
        Serial.println(": Test passed");
    } else {
        Serial.print(field);
        Serial.println(": Test failed");
    }
}
