
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

#define DISPLAY_TIME 1200

Dezibot dezibot = Dezibot();

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
  delay(500);
}

void loop() {
  // // king
  drawKing();
  delay(DISPLAY_TIME);

  // // queen
  drawQueen();
  delay(DISPLAY_TIME);

  // // rook
  drawRook();
  delay(DISPLAY_TIME);

  // knight
  drawKnight();
  delay(DISPLAY_TIME);

  // // bishop
  drawBishop();
  delay(DISPLAY_TIME);

  // pawn
  drawPawn();
  delay(DISPLAY_TIME);
}

void drawKing() {
  ECPKing kingW = ECPKing(dezibot, {A,1}, true);
  kingW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPKing kingB = ECPKing(dezibot, {A,1}, false);
  kingB.drawFigureToDisplay();
}

void drawQueen() {
  ECPQueen queenW = ECPQueen(dezibot, {A,1}, true);
  queenW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPQueen queenB = ECPQueen(dezibot, {A,1}, false);
  queenB.drawFigureToDisplay();
}

void drawRook() {
  ECPRook rookW = ECPRook(dezibot, {A,1}, true);
  rookW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPRook rookB = ECPRook(dezibot, {A,1}, false);
  rookB.drawFigureToDisplay();
}

void drawKnight() {
  ECPKnight knightW = ECPKnight(dezibot, {A,1}, true);
  knightW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPKnight knightB = ECPKnight(dezibot, {A,1}, false);
  knightB.drawFigureToDisplay();
}

void drawBishop() {
  ECPBishop bishopW = ECPBishop(dezibot, {A,1}, true);
  bishopW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPBishop bishopB = ECPBishop(dezibot, {A,1}, false);
  bishopB.drawFigureToDisplay();
}

void drawPawn() {
  ECPPawn pawnW = ECPPawn(dezibot, {A,1}, true);
  pawnW.drawFigureToDisplay();
  delay(DISPLAY_TIME);
  dezibot.display.invertColor(); // reset color from white figure
  ECPPawn pawnB = ECPPawn(dezibot, {A,1}, false);
  pawnB.drawFigureToDisplay();
}
