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
#include <ECPSignalDetection/ECPSignalDetection.h>

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
    ECPColorDetection(Dezibot &d, ECPSignalDetection &ir);    

    /**
     * @brief Calibrate threshold for white and black field using color sensor.
     * 
     */
    void calibrateFieldColor();

    /**
     * @brief Calibrate threshold for white and black field using infrared.
     * 
     */
    void calibrateIRFieldColor();

    /**
     * @brief Determine if measured value represents a white or black chess
     *        field.
     * 
     * @details Uses color detection mode of \p useInfraredColorDetection flag.
     *          Default is color detection using color sensor.
     *
     * Note that the field color detection should be calibrated for selected mode.
     * @see calibrateFieldColor, calibrateIRFieldColor
     * 
     * @return Determined field color
     */
    FieldColor getFieldColor();

    /**
     * @brief Calculate likely field color.
     * 
     * @details Uses color detection mode of \p useInfraredColorDetection flag.
     *          Default is color detection using color sensor.
     * 
     * Usecase: the determined field color is unambiguous but a likely color is need
     * 
     * Determine if measured value is closer to the black or white field threshold
     * In case the distance is identical black field is preferred
     * 
     * @return Likely fieldColor, only BLACK_FIELD and WHITE_FIELD possible
     */
    FieldColor getLikelyFieldColor();

    /**
     * @brief Set value for \p useInfraredColorDetection flag.
     * 
     * @param useIR true if infrared color detection should be used, false otherwise
     */
    void setColorDetectionMode(bool useIR);

    /**
     * @brief Return value of \p useInfraredColorDetection flag.
     * 
     * @return @see useInfraredColorDetection
     */
    bool getColorDetectionMode();

    /**
     * @brief Set value for \p shouldTurnOnColorCorrectionLight flag.
     * 
     * @param turnOn true if correction light should be turned on, false otherwise 
     */
    void setShouldTurnOnColorCorrectionLight(bool turnOn);

    /**
     * @brief Return value of \p shouldTurnOnColorCorrectionLight flag.
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

protected:
    Dezibot &dezibot;
    ECPSignalDetection &ecpSignalDetection;

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
     * @brief Lowest cumulated infrared value to be recognised as white field.
     * 
     */
    float isIRWhiteFieldThreshold = DEFAULT_IR_WHITE_THRESHOLD;

    /**
     * @brief Highest cumulated infrared value to be recognised as black field.
     * 
     */
    float isIRBlackFieldThreshold = DEFAULT_IR_BLACK_THRESHOLD;

    /**
     * @brief Flag for setting mode of color detection
     * 
     */
    bool useInfraredColorDetection = false;

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
     * @brief Calibrate infrared on white or black field.
     * 
     * @param isWhite True if color to calibrate is white, false if black
     * @return cumulatedInfraredValues as float 
     */
    float calibrateIRColor(bool isWhite);

    /**
     * @brief Measure brightness.
     * 
     * @return brightness as double
     */
    double measureBrightness();

    /**
     * @brief Determine if brightness value of color sensor clearly represents 
     *        a white or black chess field.
     *
     * Note that the field color detection should be calibrated.
     * @see calibrateFieldColor
     * 
     * @return Determined field color
     */
    FieldColor measureFieldColor();

    /**
     * @brief Calculate likely field color using color sensor.
     * 
     * Usecase: determined field color with \p measureFieldColor is 
     * unambiguous but a likely color is needed.
     * 
     * Calculate if measured brightness is closer to the black or white field threshold
     * In case the distance is identical black field is preferred
     * 
     * @return Likely fieldColor, only BLACK_FIELD and WHITE_FIELD possible
     */
    FieldColor calculateLikelyFieldColor();

    /**
     * @brief Determine if infrared values represents a white or black chess field.
     * 
     * Note that the field color detection using infrared should be calibrated.
     * @see calibrateIRFieldColor() 
     * 
     * @return Determined field color
     */
    FieldColor measureInfraredFieldColor();

    /**
     * @brief Calculate likely field color using IR signal detection.
     * 
     * Usecase: determined field color with \p measureInfraredFieldColor is 
     * unambiguous but a likely color is needed.
     * 
     * Calculate if measured brightness is closer to the black or white field threshold
     * In case the distance is identical black field is preferred
     * 
     * @return Likely fieldColor, only BLACK_FIELD and WHITE_FIELD possible
     */
    FieldColor calculateLikelyInfraredFieldColor();

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
     * @brief Default value for \p isIRWhiteFieldThreshold.
     * 
     */
    const float DEFAULT_IR_WHITE_THRESHOLD = 1.0;

    /**
     * @brief Default value for \p isIRBlackFieldThreshold.
     * 
     */
    const float DEFAULT_IR_BLACK_THRESHOLD = 0.5;

    /**
     * @brief Factor to calculate threshold offset.
     * 
     * @see isWhiteFieldThreshold, isBlackFieldThreshold
     */
    const double THRESHOLD_OFFSET = 0.025;

    /**
     * @brief Factor to calculate threshold offset.
     * 
     * Reducing the threshold offset causes field color to indicate a color when the 
     * middle of that field is reached. 
     * 
     * Note that reducing the offset may result in difficulties for movement. 
     * 
     * @see isIRWhiteFieldThreshold, isIRBlackFieldThreshold
     */
    const float THRESHOLD_OFFSET_IR = 0.2;
};

#endif // ECPColorDetection_h
