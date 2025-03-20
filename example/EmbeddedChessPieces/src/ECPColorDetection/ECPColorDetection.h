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

/**
 * @brief Color of field the dezibot is standing on.
 * 
 * Convertible to int, i.e. BLACK_FIELD == 0, WHITE_FIELD == 1
 * 
 */
enum FieldColor {
    BLACK_FIELD, 
    WHITE_FIELD,
    UNAMBIGUOUS
};

class ECPColorDetection {
public:
    ECPColorDetection(Dezibot &d);

    /**
     * @brief Determine if brightness value clearly represents a white or a black chess
     *        field.
     *
     * Note that the field color detection should be calibrated.
     * @see calibrateFieldColor() 
     * 
     * @return Determined field color
     */
    FieldColor getFieldColor();

    /**
     * @brief Determine likely field color.
     * 
     * Usecase: the determined field color is unambiguous but a likely color is need
     * 
     * Determine if measured brightness is closer to the black or white field threshold
     * In case the distance is identical black field is preferred
     * 
     * @return Likely fieldColor, only BLACK_FIELD and WHITE_FIELD possible
     */
    FieldColor getLikelyFieldColor();

    /**
     * @brief Set value for shouldTurnOnColorCorrectionLight flag.
     * 
     * @param turnOn true if correction light should be turned on else false 
     */
    void setShouldTurnOnColorCorrectionLight(bool turnOn);

    /**
     * @brief Return value of shouldTurnOnColorCorrectionLight flag.
     * 
     * @return @see shouldTurnOnColorCorrectionLight
     */
    bool getShouldTurnOnColorCorrectionLight();

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
     * @brief Calibrate threshold for white and black field.
     * 
     */
    void calibrateFieldColor();

protected:
    Dezibot &dezibot;

    /**
     * @brief Lowest value for color to be recognised as white field.
     * 
     */
    double isWhiteFieldThreshold = DEFAULT_WHITE_THRESHOLD;

    /**
     * @brief Highest value for color to be recognised as black field.
     * 
     */
    double isBlackFieldThreshold = DEFAULT_BLACK_THRESHOLD;

    /**
     * @brief Flag for setting of color correction light.
     * 
     */
    bool shouldTurnOnColorCorrectionLight = false;

private:
    /**
     * @brief Calibrate on white or black field.
     * 
     * @param isWhite True if color to calibrate is white, false if black
     * @return brightness as double 
     */
    double calibrateColor(bool isWhite);

    /**
     * @brief Measure brightness.
     * 
     * @return brightness as double
     */
    double measureBrightness();

    /**
     * @brief Time between measurements of field colors in \p calibrateColor.
     * 
     */
    const int CALIBRATION_TIME = 2000;

    /**
     * @brief How many fields are used to calibrate a field color in \p calibrateFieldColor.
     * 
     */
    const int CALIBRATE_FIELD_COUNT = 5;

    /**
     * @brief How many measurements of current brightness are averaged in \p measureBrightness.
     * 
     */
    const int MEASUREMENT_COUNT = 3;

    /**
     * @brief Time before brightness is measured in \p measureBrightness.
     * 
     */
    const int DELAY_BEFORE_MEASURING = 250;

    /**
     * @brief Default value for \p isWhiteFieldThreshold.
     * 
     */
    const double DEFAULT_WHITE_THRESHOLD = 220.0;

    /**
     * @brief Default value for \p isBlackFieldThreshold.
     * 
     */
    const double DEFAULT_BLACK_THRESHOLD = 50.0;

    /**
     * @brief Factor to calculate threshold offset.
     * 
     * @see isWhiteFieldThreshold, isBlackFieldThreshold
     */
    const double THRESHOLD_OFFSET = 0.025;
};

#endif // ECPColorDetection_h
