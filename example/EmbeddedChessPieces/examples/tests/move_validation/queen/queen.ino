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
ECPMovement ecpMovement = ECPMovement(dezibot);

int totalTestCases = 0;
int successfulTestCases = 0;

void setup() {
    Serial.begin(BAUD_RATE);
    dezibot.begin();
    delay(500);
}

void loop() {
    // reset global variables
    totalTestCases = 0;
    successfulTestCases = 0;

    Serial.println("\n\n=== STARTING TEST ===\n");
    dezibot.display.clear();
    dezibot.display.println("Testing...");
    Serial.println("Testing queen...");

    testQueen();

    Serial.println("\n=== TEST DONE ===\n");

    const String results = String(successfulTestCases) + "/"
        + String(totalTestCases) + " passed\n";
    Serial.println("==> " + results);
    dezibot.display.println(results);

    const String sleepingString = "Sleeping for 10s...";
    Serial.println(sleepingString);
    dezibot.display.println(sleepingString);

    delay(10000);
}

void testQueen() {
    const ECPChessField initialField = { D, 4 };
    ECPQueen queen = ECPQueen(dezibot, ecpMovement, initialField, true);

    // valid moves
    Serial.println("Testing valid moves...");
    const ECPChessField validFields[] = {
                                      { D, 8 },                               { H, 8 },
        { A, 7 },                     { D, 7 },                     { G, 7 },
                  { B, 6 },           { D, 6 },           { F, 6 },
                            { C, 5 }, { D, 5 }, { E, 5 },
        { A, 4 }, { B, 4 }, { C, 4 }, /* fig */ { E, 4 }, { F, 4 }, { G, 4 }, { H, 4 },
                            { C, 3 }, { D, 3 }, { E, 3 },
                  { B, 2 },           { D, 2 },           { F, 2 },          
        { A, 1 },                     { D, 1 },                     { G, 1 }};

    totalTestCases += sizeof(validFields) / sizeof(validFields[0]);

    for (const ECPChessField field : validFields) {
        const bool isSuccess = test(queen, field, true);
        if (isSuccess) {
            successfulTestCases++;
        }
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    const ECPChessField invalidFields[] = {
        initialField,
        { A, 8 }, { B, 8 }, { C, 8 },           { E, 8 }, { F, 8 }, { G, 8 },
                  { B, 7 }, { C, 7 },           { E, 7 }, { F, 7 },           { H, 7 },
        { A, 6 },           { C, 6 },           { E, 6 },           { G, 6 }, { H, 6 },
        { A, 5 }, { B, 5 },                               { F, 5 }, { G, 5 }, { H, 5 },
                                      /* fig */
        { A, 3 }, { B, 3 },                               { F, 3 }, { G, 3 }, { H, 3 },
        { A, 2 },           { C, 2 },           { E, 2 },           { G, 2 }, { H, 2 },
                  { B, 1 }, { C, 1 },           { E, 1 }, { F, 1 },           { H, 1 }};

    totalTestCases += sizeof(invalidFields) / sizeof(invalidFields[0]);

    for (const ECPChessField field : invalidFields) {
        const bool isSuccess = test(queen, field, false);
        if (isSuccess) {
            successfulTestCases++;
        }
    }
}

bool test(ECPChessPiece& piece, ECPChessField field, bool expected) {
    const bool actual = piece.isMoveValid(field);
    const bool didTestPass = (actual == expected);

    Serial.print(field.toString() + ": ");
    if (didTestPass) {
        Serial.println("Test passed");
    } else {
        Serial.println("Test failed");
    }

    return didTestPass;
}
