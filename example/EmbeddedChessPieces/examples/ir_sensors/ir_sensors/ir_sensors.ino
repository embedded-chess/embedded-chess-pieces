/**
 * @file ir_sensors.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Test sketch for receiving IR light
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>

#define BAUD_RATE 9600

#define MEAS_COUNT 3
#define TIME_BETWEEN_MEAS 1 // ms

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(BAUD_RATE);
    dezibot.begin();
    dezibot.display.flipOrientation();
    delay(10);
}

void loop() {
    const photoTransistors sensors[] = { IR_FRONT, IR_RIGHT, IR_BACK, IR_LEFT };

    dezibot.display.clear();
    for (const photoTransistors sensor : sensors) {
        const int irValue = dezibot.lightDetection.getAverageValue(
            sensor,
            MEAS_COUNT,
            TIME_BETWEEN_MEAS
        );
        const float normalizedValue = dezibot.lightDetection.normalizeValue(irValue);
        printValue(normalizedValue, sensor);
    }

    delay(500);
}

void printValue(float irValue, photoTransistors sensor) {
    const String s = ptString(sensor);
    dezibot.display.print(s + " ");
    Serial.print(s);

    dezibot.display.println(String(irValue));
    Serial.println(irValue);
}

String ptString(photoTransistors sensor) {
    switch (sensor) {
        case IR_LEFT:
            return "W";
        case IR_RIGHT:
            return "E";
        case IR_FRONT:
            return "N";
        case IR_BACK:
            return "S";
        default:
            return " ";
    }
}
