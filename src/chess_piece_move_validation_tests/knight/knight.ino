/**
 * @file knight.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test for ECPKnight isMoveValid method.
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

    Serial.println("Testing knight...");
    testKnight();

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}

void testKnight() {
    const ECPChessField initialField = { D, 5 };
    ECPKnight knight = ECPKnight(dezibot, initialField, true);

    // valid moves
    Serial.println("Testing valid moves...");
    ECPChessField validFields[] = {{ C, 7 }, { E, 7 }, { F, 6 }, { F, 4 },
        { E, 3 }, { C, 3 }, { B, 4}, { B, 6 }};
    for (ECPChessField field : validFields) {
        test(knight, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {
        initialField,
        // directly surrounding fields
        { C, 6}, { D, 6 }, { E, 6 }, { E, 5 }, { E, 4 }, { D, 4}, { C, 4}, { C, 5 },
        // surrounding + 1
        { B, 7 }, { D, 7 }, { F, 7 }, { F, 5}, { F, 3 }, { D, 3 }, { B, 3 }, { B, 5 },
        // surrounding + 2
        { A, 8 }, { B, 8 }, { C, 8 }, { D, 8 }, { E, 8 }, { F, 8 }, { G, 8 },
        { G, 7 }, { G, 6 }, { G, 5 }, { G, 4 }, { G, 3 }, { G, 2 },
        { F, 2 }, { E, 2 }, { D, 2 }, { C, 2 }, { B, 2 }, { A, 2},
        { A, 3 }, { A, 4 }, { A, 5 }, { A, 6 }, { A, 7 }
    };
    for (ECPChessField field : invalidFields) {
        test(knight, field, false);
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
