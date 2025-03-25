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

void loop() {}
