/**
 * @file rotate_90.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to test the rotation of the Dezibot
 * @version 0.1
 * @date 2024-12-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>

// change for a calibration fitting the specific dezibot
#define MOVEMENT_CALIBRATION 3900

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement(dezibot, MOVEMENT_CALIBRATION);

void setup() {
  dezibot.begin();
  dezibot.display.flipOrientation();
  delay(500);
}

void loop() {
  dezibot.display.println("Turning left...");
  ecpMovement.turnLeft({A, 1}, WEST);
  dezibot.display.println("Done");
  delay(10000);

  dezibot.display.println("Turning right...");
  ecpMovement.turnRight({A, 1}, NORTH);
  dezibot.display.println("Done");
  
  dezibot.display.println("\Sleep 10s");
  delay(10000);
  dezibot.display.clear();
}
