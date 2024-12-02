/**
 * @file queen.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test for ECPQueen isMoveValid method.
 * @version 0.1
 * @date 2024-12-02
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

    Serial.println("Testing queen...");
    testQueen();

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}

void testQueen() {
    const ECPChessField initialField = { D, 4 };
    ECPQueen queen = ECPQueen(dezibot, initialField, true);

    // valid moves
    Serial.println("Testing valid moves...");
    ECPChessField validFields[] = {
                                      { D, 8 },                               { H, 8 },
        { A, 7 },                     { D, 7 },                     { G, 7 },
                  { B, 6 },           { D, 6 },           { F, 6 },
                            { C, 5 }, { D, 5 }, { E, 5 },
        { A, 4 }, { B, 4 }, { C, 4 }, /* fig */ { E, 4 }, { F, 4 }, { G, 4 }, { H, 4 },
                            { C, 3 }, { D, 3 }, { E, 3 },
                  { B, 2 },           { D, 2 },           { F, 2 },          
        { A, 1 },                     { D, 1 },                     { G, 1 }
    };
    for (ECPChessField field : validFields) {
        test(queen, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {
        initialField,
        { A, 8 }, { B, 8 }, { C, 8 },           { E, 8 }, { F, 8 }, { G, 8 },
                  { B, 7 }, { C, 7 },           { E, 7 }, { F, 7 },           { H, 7 },
        { A, 6 },           { C, 6 },           { E, 6 },           { G, 6 }, { H, 6 },
        { A, 5 }, { B, 5 },                               { F, 5 }, { G, 5 }, { H, 5 },
                                      /* fig */
        { A, 3 }, { B, 3 },                               { F, 3 }, { G, 3 }, { H, 3 },
        { A, 2 },           { C, 2 },           { E, 2 },           { G, 2 }, { H, 2 },
                  { B, 1 }, { C, 1 },           { E, 1 }, { F, 1 },           { H, 1 }
    };
    for (ECPChessField field : invalidFields) {
        test(queen, field, false);
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
