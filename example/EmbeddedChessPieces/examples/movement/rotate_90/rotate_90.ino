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
#include <Wire.h>

// change for a calibration fitting the specific dezibot
#define MOVEMENT_CALIBRATION 3900
#define ROTATION_TIME_LEFT 2750
#define ROTATION_TIME_RIGHT 2550

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement(
  dezibot, 
  MOVEMENT_CALIBRATION, 
  ROTATION_TIME_LEFT, 
  ROTATION_TIME_RIGHT
);
ECPColorDetection ecpColorDetection(dezibot);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
  delay(500);
}

void loop() {
  dezibot.display.println("Turning left...");
  ecpMovement.turnLeft();
  dezibot.display.println("Done");
  delay(2000);

  dezibot.display.println("Turning right...");
  ecpMovement.turnRight();
  dezibot.display.println("Done");
  
  dezibot.display.println("\nSleeping for 10s...");
  delay(10000);
  dezibot.display.clear();
}
