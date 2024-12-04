/**
 * @file chess_field_exception.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test ECPChessField to throw when passing invalid values.
 * @version 0.1
 * @date 2024-12-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <EmbeddedChessPieces.h>
#include <Wire.h>

#define BAUD_RATE 9600

void setup() {
    Serial.begin(BAUD_RATE);
    delay(500);
}

void loop() {
    Serial.println("\n=== STARTING TEST ===\n");

    try {
      const ECPChessField invalidField = { A, 9 };
      Serial.println("Case 1 failed");
    } catch (...) {
      Serial.println("Case 1 passed");
    }

    try {
      const ECPChessField invalidField = { A, 0 };
      Serial.println("Case 2 failed");
    } catch (...) {
      Serial.println("Case 2 passed");
    }

    Serial.println("\n=== TEST DONE ===");
    Serial.println("Sleeping for 10 seconds...\n");

    delay(10000);
}
