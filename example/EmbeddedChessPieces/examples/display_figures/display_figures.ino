
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
  delay(10000);
  dezibot.display.clear();
  drawQueen();
  delay(10000);
  dezibot.display.clear();
  drawRook();
  delay(10000);
  dezibot.display.clear();
}

void drawKing() {
  dezibot.display.println(" __        __   ");
  dezibot.display.println("|  n____  /  \\  ");
  dezibot.display.println("|  |    |#   /  ");
  dezibot.display.println("|  |    |#   \\  ");
  dezibot.display.println("|  |    |#    )+");
  dezibot.display.println("|  |    |#   /  ");
  dezibot.display.println("|  |____|#   \\  ");
  dezibot.display.println("|__u      \\__/  ");
}

void drawQueen() {
  dezibot.display.println(" __        __   ");
  dezibot.display.println("|  n____  /  >o ");
  dezibot.display.println("|  |    |#  <   ");
  dezibot.display.println("|  |    |#   >o ");
  dezibot.display.println("|  |    |#  <   ");
  dezibot.display.println("|  |    |#   >o ");
  dezibot.display.println("|  |____|#  <   ");
  dezibot.display.println("|__u      \\__>o ");
}

void drawRook() {
  dezibot.display.println(" __        ___  ");
  dezibot.display.println("|  n____ _/   | ");
  dezibot.display.println("|  |    #   |=  ");
  dezibot.display.println("|  |    #     | ");
  dezibot.display.println("|  |    #   |=  ");
  dezibot.display.println("|  |    #     | ");
  dezibot.display.println("|  |____#_  |=  ");
  dezibot.display.println("|__u      \\___| ");
}
