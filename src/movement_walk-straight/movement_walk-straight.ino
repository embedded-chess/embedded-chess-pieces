/**
 * @file movement_walk-straight.ino
 * @author Ines Rohrbach
 * @brief Example to test the straight movement of the Dezibot
 * @version 0.1
 * @date 2024-10-30
 * 
 * @copyright Copyright (c) 2024
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
}

void loop() {
  bool isOnWhite = isChessFieldColorWhite();
  moveToNextField(isOnWhite);

  dezibot.display.println("Break");
  delay(10000);
}

/**
 * @brief Move straight to the next field.
 * 
 * @param isOnWhite information if the dezibot starts on a white field
*/
void moveToNextField(bool isOnWhite) {
  int MOVE_STRAIGHT_TIME_INTERVALL = 1000;
  bool isWhiteField = isChessFieldColorWhite();  

  while (isWhiteField == isOnWhite) {
    dezibot.display.print("Is on ");
    dezibot.display.println(isWhiteString(isWhiteField));
    dezibot.display.print("Wants ");
    dezibot.display.println(isWhiteString(!isOnWhite));
  
    dezibot.display.println("Moving...");
    move(MOVE_STRAIGHT_TIME_INTERVALL);
  
    isWhiteField = isChessFieldColorWhite();
    dezibot.display.clear();
  }
}

/**
 * @brief 
 *
 * @param isWhite as bool - true if field is determined as white
 * @return String - if isWhite is true then "W" else "B"
*/
String isWhiteString(bool isWhite) {
  return isWhite ? "W" : "B" ;
}

/**
 * @brief Move straight for the given amount of time.
 * 
 * @param time in ms - how long the dezibot should move.
*/
void move(int time) {
  dezibot.motion.move();
  delay(time);
  dezibot.motion.stop();
}

/**
 * @brief Check if the field under the dezibot is white.
 * 
 * @return true if the field is white
 * @return false if the field is black
*/
bool isChessFieldColorWhite() {
  double ambient = dezibot.chessColorDetection.getNormalizedAmbientValue();

  double red = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_RED, ambient);
  double green = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_GREEN, ambient);
  double blue = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_BLUE, ambient);

  double brightness = dezibot.chessColorDetection.calculateBrightness(red, green, blue);
  bool isWhite = dezibot.chessColorDetection.isWhiteField(brightness);

  return isWhite;
}
