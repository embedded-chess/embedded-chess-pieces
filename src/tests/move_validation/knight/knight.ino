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
    ECPChessField validFields[] = {
                  { C, 7 },           { E, 7 },
        { B, 6 },                               { F, 6 },
                            /* fig */
        { B, 4 },                               { F, 4 },
                  { C, 3 },           { E, 3 }};
    for (ECPChessField field : validFields) {
        test(knight, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {
        initialField,
        { A, 8 }, { B, 8 }, { C, 8 }, { D, 8 }, { E, 8 }, { F, 8 }, { G, 8 }, { H, 8 },
        { A, 7 }, { B, 7 },           { D, 7 },           { F, 7 }, { G, 7 }, { H, 7 },
        { A, 6 },           { C, 6 }, { D, 6 }, { E, 6 },           { G, 6 }, { H, 6 },
        { A, 5 }, { B, 5 }, { C, 5 }, /* fig */ { E, 5 }, { F, 5 }, { G, 5 }, { H, 5 },
        { A, 4 },           { C, 4 }, { D, 4 }, { E, 4 },           { G, 4 }, { H, 4 },
        { A, 3 }, { B, 3 },           { D, 3 },           { F, 3 }, { G, 3 }, { H, 3 },
        { A, 2 }, { B, 2 }, { C, 2 }, { D, 2 }, { E, 2 }, { F, 2 }, { G, 2 }, { H, 2 },
        { A, 1 }, { B, 1 }, { C, 1 }, { D, 1 }, { E, 1 }, { F, 1 }, { G, 1 }, { H, 1 }};
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
