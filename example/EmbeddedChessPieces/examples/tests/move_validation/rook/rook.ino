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

    Serial.println("Testing rook on initial field...");
    testRookOnInitialField();
    Serial.println("\nTesting rook in board center...");
    testRookInBoardCenter();

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

void testRookOnInitialField() {
    const ECPChessField initialField = { A, 1 };
    ECPRook rook = ECPRook(dezibot, ecpMovement, initialField, true);

    // valid moves
    Serial.println("\nTesting valid moves...");
    const ECPChessField validFields[] = {
        { A, 8 },
        { A, 7 },
        { A, 6 },
        { A, 5 },
        { A, 4 },
        { A, 3 },
        { A, 2 },
        /* fig */ { B, 1 }, { C, 1 }, { D, 1 }, { E, 1 }, { F, 1 }, { G, 1 }, { H, 1 }};

    totalTestCases += sizeof(validFields) / sizeof(validFields[0]);

    for (const ECPChessField field : validFields) {
        const bool isSuccess = test(rook, field, true);
        if (isSuccess) {
            successfulTestCases++;
        }
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    const ECPChessField invalidFields[] = {
        initialField,
                  { B, 8 }, { C, 8 }, { D, 8 }, { E, 8 }, { F, 8 }, { G, 8 }, { H, 8 },
                  { B, 7 }, { C, 7 }, { D, 7 }, { E, 7 }, { F, 7 }, { G, 7 }, { H, 7 },
                  { B, 6 }, { C, 6 }, { D, 6 }, { E, 6 }, { F, 6 }, { G, 6 }, { H, 6 },
                  { B, 5 }, { C, 5 }, { D, 5 }, { E, 5 }, { F, 5 }, { G, 5 }, { H, 5 },
                  { B, 4 }, { C, 4 }, { D, 4 }, { E, 4 }, { F, 4 }, { G, 4 }, { H, 4 },
                  { B, 3 }, { C, 3 }, { D, 3 }, { E, 3 }, { F, 3 }, { G, 3 }, { H, 3 },
                  { B, 2 }, { C, 2 }, { D, 2 }, { E, 2 }, { F, 2 }, { G, 2 }, { H, 2 },
        /* fig */ };
    
    totalTestCases += sizeof(invalidFields) / sizeof(invalidFields[0]);

    for (const ECPChessField field : invalidFields) {
        const bool isSuccess = test(rook, field, false);
        if (isSuccess) {
            successfulTestCases++;
        }
    }
}

void testRookInBoardCenter() {
    const ECPChessField initialField = { D, 5 };
    ECPRook rook = ECPRook(dezibot, ecpMovement, initialField, false);

    // valid moves
    Serial.println("\nTesting valid moves...");
    const ECPChessField validFields[] = {
                                      { D, 8 },
                                      { D, 7 },
                                      { D, 6 },
        { A, 5 }, { B, 5 }, { C, 5 }, /* fig */ { E, 5 }, { F, 5 }, { G, 5 }, { H, 5 },
                                      { D, 4 },
                                      { D, 3 },
                                      { D, 2 },
                                      { D, 1 }};

    totalTestCases += sizeof(validFields) / sizeof(validFields[0]);

    for (const ECPChessField field : validFields) {
        const bool isSuccess = test(rook, field, true);
        if (isSuccess) {
            successfulTestCases++;
        }
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    const ECPChessField invalidFields[] = {
        initialField,
        { A, 8 }, { B, 8 }, { C, 8 },           { E, 8 }, { F, 8 }, { G, 8 }, { H, 8 },
        { A, 7 }, { B, 7 }, { C, 7 },           { E, 7 }, { F, 7 }, { G, 7 }, { H, 7 },
        { A, 6 }, { B, 6 }, { C, 6 },           { E, 6 }, { F, 6 }, { G, 6 }, { H, 6 },
                                      /* fig */
        { A, 4 }, { B, 4 }, { C, 4 },           { E, 4 }, { F, 4 }, { G, 4 }, { H, 4 },
        { A, 3 }, { B, 3 }, { C, 3 },           { E, 3 }, { F, 3 }, { G, 3 }, { H, 3 },
        { A, 2 }, { B, 2 }, { C, 2 },           { E, 2 }, { F, 2 }, { G, 2 }, { H, 2 },
        { A, 1 }, { B, 1 }, { C, 1 },           { E, 1 }, { F, 1 }, { G, 1 }, { H, 1 }};
    
    totalTestCases += sizeof(invalidFields) / sizeof(invalidFields[0]);
    
    for (const ECPChessField field : invalidFields) {
        const bool isSuccess = test(rook, field, false);
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
