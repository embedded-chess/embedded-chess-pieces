/**
 * @file ir_emitter.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Sketch to periodically emit IR light
 * @version 0.1
 * @date 2025-03-23
 * 
 * @note Does not reliably turn infrared light on and off as well as recognise
 *       infrared light from another dezibot.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>

Dezibot dezibot = Dezibot();

void setup() {
    dezibot.begin();
    delay(100);
}

bool turnedOn = false;

void loop() {
    const float irValue = dezibot.lightDetection.normalizeValue(
        dezibot.lightDetection.getAverageValue(IR_FRONT, 3, 50)
    );

    if ((irValue > 0.1f)) {
        if (turnedOn) {
            dezibot.infraredLight.front.turnOff();
            turnedOn = false;

            dezibot.display.clear();
            dezibot.display.println("IR turned off");
            delay(500);
        }
    } else {
        if (!turnedOn) {
            dezibot.infraredLight.front.turnOn();
            turnedOn = true;

            dezibot.display.clear();
            dezibot.display.println("IR turned on");
            delay(1000);
        }
    }
    
    delay(100);
}
