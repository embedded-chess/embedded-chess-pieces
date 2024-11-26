/**
 * @file king.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test for ECPKing isMoveValid method.
 * @version 0.1
 * @date 2024-11-26
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

    Serial.println("Testing king...");
    testKing();

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}

void testKing() {
    const ECPChessField initialField = { F, 5 };
    ECPKing king = ECPKing(dezibot, initialField, true);

    // valid moves
    Serial.println("Testing valid moves...");
    ECPChessField validFields[] = {{ E, 6}, { F, 6}, { G, 6}, { G, 5}, { G, 4},
        { F, 4}, { E, 4}, { E, 5}};
    for (ECPChessField field : validFields) {
        test(king, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {initialField, { D, 7}, { E, 7}, { F, 7},
        { G, 7}, { H, 7}, { H, 6}, { H, 5}, { H, 4}, { H, 3}, { G, 3}, { F, 3},
        { E, 3}, { D, 3}, { D, 4}, { D, 5}, { D, 6}};
    for (ECPChessField field : invalidFields) {
        test(king, field, false);
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
