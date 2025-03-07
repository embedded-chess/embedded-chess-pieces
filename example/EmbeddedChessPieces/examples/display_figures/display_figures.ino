
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
ECPMovement ecpMovement = ECPMovement(dezibot);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");
  delay(500);
}

void loop() {
  drawKing();
  delay(DISPLAY_TIME);

  drawQueen();
  delay(DISPLAY_TIME);

  drawRook();
  delay(DISPLAY_TIME);

  drawKnight();
  delay(DISPLAY_TIME);

  drawBishop();
  delay(DISPLAY_TIME);

  drawPawn();
  delay(DISPLAY_TIME);
}

void drawKing() {
  ECPKing kingW = ECPKing(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPKing kingB = ECPKing(dezibot, ecpMovement, {A,1}, false);
}

void drawQueen() {
  ECPQueen queenW = ECPQueen(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPQueen queenB = ECPQueen(dezibot, ecpMovement, {A,1}, false);
}

void drawRook() {
  ECPRook rookW = ECPRook(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPRook rookB = ECPRook(dezibot, ecpMovement, {A,1}, false);
}

void drawKnight() {
  ECPKnight knightW = ECPKnight(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPKnight knightB = ECPKnight(dezibot, ecpMovement, {A,1}, false);
}

void drawBishop() {
  ECPBishop bishopW = ECPBishop(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPBishop bishopB = ECPBishop(dezibot, ecpMovement, {A,1}, false);
}

void drawPawn() {
  ECPPawn pawnW = ECPPawn(dezibot, ecpMovement, {A,1}, true);
  delay(DISPLAY_TIME);
  ECPPawn pawnB = ECPPawn(dezibot, ecpMovement, {A,1}, false);
}
