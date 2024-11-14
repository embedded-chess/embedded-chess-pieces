/**
 * @file movement_walk-straight.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to test the straight movement of the Dezibot
 * @version 0.1
 * @date 2024-10-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement(dezibot, 4050);
ECPColorDetection ecpColorDetection(dezibot);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
  ecpColorDetection.turnOnColorCorrectionLight();
}

void loop() {
  uint numberOfFields = 2;
  dezibot.display.println("Moving 2 Fields");
  dezibot.display.println("...");
  ecpMovement.move(numberOfFields);

  dezibot.display.println("");
  dezibot.display.println("Taking a break");
  delay(10000);
  dezibot.display.clear();
}
