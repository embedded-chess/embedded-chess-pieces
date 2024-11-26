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
    Serial.println("\nTesting valid moves...");
    ECPChessField validFields[] = {{ A, 2 }, { A, 8 }, { B, 1 }, { H, 1 }};
    for (ECPChessField field : validFields) {
        test(rook, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {initialField, { B, 4 }, { B, 8 }, { H, 8 }};
    for (ECPChessField field : invalidFields) {
        test(rook, field, false);
    }
}

void testRookInBoardCenter() {
    const ECPChessField initialField = { D, 5 };
    ECPRook rook = ECPRook(dezibot, initialField, false);

    // valid moves - horizontally
    Serial.println("\nTesting valid horizontal moves...");
    ECPChessField validHorizontalFields[] = {{ A, 5 }, { B, 5 }, { C, 5 },
        { E, 5 }, { F, 5 }, { G, 5 }, { H, 5 }};
    for (ECPChessField field : validHorizontalFields) {
        test(rook, field, true);
    }

    // valid moves - vertically
    Serial.println("\nTesting valid vertical moves...");
    ECPChessField validVerticalFields[] = {{ D, 1 }, { D, 2 }, { D, 3 },
        { D, 4 }, { D, 6 }, { D, 7 }, { D, 8 }};
    for (ECPChessField field : validVerticalFields) {
        test(rook, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {initialField, { D, 5 }, { C, 4 }, { C, 6 },
        { E, 6 }, { E, 4 }};
    for (ECPChessField field : invalidFields) {
        test(rook, field, false);
    }
}

void test(ECPChessPiece& piece, ECPChessField field, bool expected) {
    bool actual = piece.isMoveValid(field);

    Serial.print(field.toString() + ": ");
    if (actual == expected) {
        Serial.println("Test passed");
    } else {
        Serial.println("Test failed");
    }
}
