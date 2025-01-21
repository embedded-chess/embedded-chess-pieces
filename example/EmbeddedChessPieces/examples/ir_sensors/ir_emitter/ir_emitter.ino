/**
 * @file ir_emitter.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Sketch to emit IR light
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>

Dezibot dezibot = Dezibot();

void setup() {
    dezibot.begin();
    delay(10);

    dezibot.infraredLight.front.turnOn();
    dezibot.display.println("IR turned on");
}

void loop() {
    // dezibot.infraredLight.front.turnOn();
    // dezibot.display.println("IR turned on");
    // delay(10000);

    // dezibot.infraredLight.front.turnOff();
    // dezibot.display.println("IR turned off");
    // delay(10000);
}
