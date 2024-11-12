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

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
}

void loop() {
  dezibot.display.println("Moving");
  dezibot.display.println("...");
  ecpMovement.move();

  dezibot.display.println("");
  dezibot.display.println("Taking a break");
  delay(10000);
  dezibot.display.clear();
}
