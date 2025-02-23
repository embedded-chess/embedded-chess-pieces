/**
 * @file ECPSignalDetection.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper class for IR signal detection
 * @version 0.1
 * @date 2025-02-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ECPSignalDetection_H
#define ECPSignalDetection_H

#include <cmath>

#include <Dezibot.h>

class ECPSignalDetection{
protected:
    Dezibot &dezibot;

public:
    ECPSignalDetection(Dezibot &dezibot);

    /**
     * @brief Measure infrared signal angle where 0° is equivalent to north.
     * 
     * @return int Angle in degrees, i.e. [0, 360].
     *             Returns -1 if no signal was detected or was too weak.
     */
    int measureSignalAngle();

private:
    static const int MEASUREMENT_COUNT = 3;
    static const int TIME_BETWEEN_MEASUREMENTS = 1; // in ms
    static constexpr float MIN_THRESHOLD_MEASUREMENTS = 0.10f;
};

#endif // ECPSignalDetection_H
