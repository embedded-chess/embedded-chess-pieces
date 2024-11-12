/**
 * @file ECPColorDetection.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper class for color detection
 * @version 0.1
 * @date 2024-10-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPColorDetection_h
#define ECPColorDetection_h

#include <Dezibot.h>

#define IS_WHITE_FIELD_THRESHOLD 100.0

#define COLOR_CORRECTION_LIGHT_R 43
#define COLOR_CORRECTION_LIGHT_G 33
#define COLOR_CORRECTION_LIGHT_B 35

class ECPColorDetection {
protected:
    Dezibot &dezibot;

public:
    ECPColorDetection(Dezibot &d);

    /**
     * @brief Determine if brightness value represents a white or a black chess
     *        field.
     *
     * Note that the room must be well-lit or color correction light is turned on
     * (see \see turnOnColorCorrectionLight).
     * At a normalized ambient light of about 10.0 or lower white field will be interpreted as black.
     * 
     * @return true if surface is white-ish
     * @return false if surface is black-ish
     */
    bool isWhiteField();

    /**
     * @brief Turn on the LED on the bottom of the Dezibot.
     * 
     * The light should help the identification of the field color even in a dimly-lit room.
     */
    void turnOnColorCorrectionLight();

    /**
     * @brief Turn off the LED on the bottom of the Dezibot.
     * 
     */
    void turnOffColorCorrectionLight();
};

#endif // ECPColorDetection_h
