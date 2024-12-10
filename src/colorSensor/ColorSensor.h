/**
 * @file ColorSensor.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper class for VEML6040 color sensor.
 * @version 0.1
 * @date 2024-10-31
 * 
 * @copyright Copyright (c) 2024
*/

#ifndef ChessColorDetection_h
#define ChessColorDetection_h

#include <algorithm>
#include <veml6040.h>

#define MAX_NORMALIZED_COLOR_VALUE 255.0
#define MAX_RAW_AMBIENT_VALUE 2061.0
#define MAX_RGBW_SENSOR_VALUE 65535.0

/**
 * @brief Controller for VEML6040 color sensor of the Dezibot.
 * 
 */
class ColorSensor {
protected:
    VEML6040 rgbwSensor;
    
public:
    enum Color {
        RED,
        GREEN,
        BLUE,
        WHITE
    };

    /**
     * @brief Initialize VEML6040 color sensor and begin transmission
     * 
     * @return true if sensor was started successfully
     * @return false if sensor could not be started
     */
    bool begin();

    /**
     * @brief Get normalized value of ambient light sensor on a scale from 0 to 255.
     * 
     * @return double normalized value
     */
    double getNormalizedAmbientValue();

    /**
     * @brief Get raw color value of RGBW sensor (**not** normalized!).
     *
     * Raw value is scaled on 16 bits.
     * For normalized value see \p getNormalizedColorValue.
     * 
     * @param color color which to get
     * @return double color value
     */
    double getRawColorValue(Color color);

    /**
     * @brief Get the normalized value of color sensor on a scale of 0 to 255 based
     *        on ambient lighting conditions.
     *
     * For \p ambientLightValue please use \p getNormalizedColorValue.
     * 
     * @param color color which to get value for
     * @param ambientLightValue **normalized** value of ambient light sensor
     * @return double normalized color value
     */
    double getNormalizedColorValue(Color color, double normalizedAmbientLight);

    /**
     * @brief Get the sensor's correlated color temperature (CCT) value in Kelvin.
     * 
     * @return double raw cct value in Kelvin
     */
    double getCCT();

    /**
     * @brief Approximate brightness value based on **normalized** RGB values.
     * 
     * This method uses the approximation algorithm proposed in
     * https://www.w3.org/TR/AERT/#color-contrast.
     * The approximated value is normalized to a scale of 0 to 255.
     * 
     * @param red normalized red value
     * @param green normalized green value
     * @param blue normalized blue value
     * @return double approximation for color value
     */
    double calculateBrightness(double red, double green, double blue);
};

#endif // ChessColorDetection_h
