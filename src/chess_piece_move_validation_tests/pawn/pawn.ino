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
    delay(500);
}

void loop() {
    Serial.println("\n=== STARTING TEST ===\n");

    Serial.println("Testing white pawn...");
    testWhitePawn();
    Serial.println("\nTesting black pawn...");
    testBlackPawn();

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}

void testWhitePawn() {
    const ECPChessField initialField = { A, 2 };
    ECPPawn pawn = ECPPawn(dezibot, initialField, true);

    // valid moves
    Serial.println("Testing valid moves...");
    ECPChessField validFields[] = {
        { A, 3}, { A, 4 },
        { B, 3 }};  // assuming that there is an opponent to capture
    for (ECPChessField field : validFields) {
        test(pawn, field, true);
    }
    
    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {initialField, { A, 1 }, { A, 5 }, { B, 2 }, { B, 1}};
    for (ECPChessField field : invalidFields) {
        test(pawn, field, false);
    }
}

void testBlackPawn() {
    const ECPChessField initialField = { C, 7 };
    ECPPawn pawn = ECPPawn(dezibot, initialField, false);

    // valid moves
    Serial.println("Testing valid moves...");
    ECPChessField validFields[] = {
        { C, 6}, { C, 5 },
        { D, 6 }};  // assuming that there is an opponent to capture
    for (ECPChessField field : validFields) {
        test(pawn, field, true);
    }

    // invalid moves
    Serial.println("\nTesting invalid moves...");
    ECPChessField invalidFields[] = {initialField, { C, 1 }, { C, 4 }, { B, 7 }, { D, 8 }};
    for (ECPChessField field : invalidFields) {
        test(pawn, field, false);
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
