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

#define COLOR_CORRECTION_LIGHT_R 43
#define COLOR_CORRECTION_LIGHT_G 33
#define COLOR_CORRECTION_LIGHT_B 35

#define CALIBRATION_TIME 5000

class ECPColorDetection {
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

    /**
     * @brief Calibrate threshold for white and black field
     * 
     */
    void calibrateFieldColor();

protected:
    Dezibot &dezibot;

    /**
     * @brief Threshold for color to be recognised as white field
     * 
     */
    double isWhiteFieldThreshold;

    /**
     * @brief Threshold for color to be recognised as black field
     * 
     */
    double isBlackFieldThreshold;

private:
    /**
     * @brief Calibrate on white or black field
     * 
     * @param isWhite True if color to calibrate is white, false if black
     * @return brightness as double 
     */
    double calibrateColor(bool isWhite);
};

#endif // ECPColorDetection_h
