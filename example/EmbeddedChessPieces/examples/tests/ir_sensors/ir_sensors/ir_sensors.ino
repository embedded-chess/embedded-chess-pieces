/**
 * @file ir_sensors.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test sketch for measuring the angle of an IR signal
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>

Dezibot dezibot = Dezibot();
ECPSignalDetection ecpSignalDetection = ECPSignalDetection(dezibot);

void setup() {
    dezibot.begin();
    dezibot.display.flipOrientation();
    delay(100);
}

void loop() {
    dezibot.display.clear();

    int signalAngle = ecpSignalDetection.measureSignalAngle();
    dezibot.display.println("S: " + String(signalAngle));

    int dezibotAngle = ecpSignalDetection.measureDezibotAngle();
    dezibot.display.println("D: " + String(dezibotAngle));

    delay(500);
}
