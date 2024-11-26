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
    test(king.isMoveValid({ E, 6}), true, "E6");
    test(king.isMoveValid({ F, 6}), true, "F6");
    test(king.isMoveValid({ G, 6}), true, "G6");
    test(king.isMoveValid({ G, 5}), true, "G5");
    test(king.isMoveValid({ G, 4}), true, "G4");
    test(king.isMoveValid({ F, 4}), true, "F4");
    test(king.isMoveValid({ E, 4}), true, "E4");
    test(king.isMoveValid({ E, 5}), true, "E5");

    // invalid moves
    test(king.isMoveValid(initialField), false, "F5");
    test(king.isMoveValid({ D, 7}), false, "D7");
    test(king.isMoveValid({ E, 7}), false, "E7");
    test(king.isMoveValid({ F, 7}), false, "F7");
    test(king.isMoveValid({ G, 7}), false, "G7");
    test(king.isMoveValid({ H, 7}), false, "H7");
    test(king.isMoveValid({ H, 6}), false, "H6");
    test(king.isMoveValid({ H, 5}), false, "H5");
    test(king.isMoveValid({ H, 4}), false, "H4");
    test(king.isMoveValid({ H, 3}), false, "H3");
    test(king.isMoveValid({ G, 3}), false, "G3");
    test(king.isMoveValid({ F, 3}), false, "F3");
    test(king.isMoveValid({ E, 3}), false, "E3");
    test(king.isMoveValid({ D, 3}), false, "D3");
    test(king.isMoveValid({ D, 4}), false, "D4");
    test(king.isMoveValid({ D, 5}), false, "D5");
    test(king.isMoveValid({ D, 6}), false, "D6");
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
