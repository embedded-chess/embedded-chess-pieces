
/**
 * @file display_figures.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to test the display of the chess figures
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

Dezibot dezibot = Dezibot();

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
  delay(500);
}

void loop() {
  drawKing();
  delay(5000);

  // reset color from white king
  dezibot.display.invertColor();

  drawQueen();
  delay(5000);

  drawRook();
  delay(5000);
}

void drawKing() {
  ECPKing kingW = ECPKing(dezibot, {A,1}, true);
  kingW.drawFigureToDisplay();
}

void drawQueen() {
  ECPQueen queenB = ECPQueen(dezibot, {A,1}, false);
  queenB.drawFigureToDisplay();
}

void drawRook() {
  ECPRook rookB = ECPRook(dezibot, {A,1}, false);
  rookB.drawFigureToDisplay();
}
