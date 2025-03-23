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
     * If no signal could be detected, print a corresponding info text on the
     * dezibot's display, wait for 1 second and try again.
     * 
     * @warning This function may <b>loop and never return</b> if no infrared
     *          signal could be detected! Make sure to place a dezibot running
     *          <tt>examples/ir_emitter.ino</tt> within reach.
     * 
     * @attention This function measures the angle from which the <b>signal</b>
     *            is coming from, <b>not</b> where the dezibot is facing. For
     *            that, refer to \p measureDezibotAngle.
     * 
     * @return int Angle in degrees, i.e. [0, 360], if signal was detected.
     */
    int measureSignalAngle();

    /**
     * @brief Measure angle the dezibot is facing based on infrared signal.
     * 
     * @details Uses \p measureSignalAngle to get signal measurement.
     * 
     * @warning This function may <b>loop and never return</b> if no infrared
     *          signal could be detected! Make sure to place a dezibot running
     *          <tt>examples/ir_emitter.ino</tt> within reach.
     * 
     * @return int angle in which dezibot is facing.
     * 
     * @see measureSignalAngle for details on how IR signal is measured
     */
    int measureDezibotAngle();

    /**
     * @brief Measure infrared values and cumulate them.
     * 
     * @param turnOnIRLight, true if bottom IR LED should be turned on 
     *        while measuring, default is true
     * @return cumulated infrared values as int (not normalized).
     */
    int cumulateInfraredValues(bool turnOnIRLight = true);

private:
    /**
     * @brief How many infrared signals are averaged in \p measureSignalAngle.
     * 
     */
    static const int MEASUREMENT_COUNT = 3;

    /**
     * @brief Time between measurements that are averaged to one in
     *        \p measureSignalAngle and \p cumulateInfraredValues in ms.
     * 
     */
    static const int TIME_BETWEEN_MEASUREMENTS = 30;

    /**
     * @brief Minimal threshold necessary to be measured before being discarded
     *        as too weak.
     * 
     * Prevent interpreting signals that are not emitted by the IR emitting
     * dezibot, caused, for example, by environmental influences.
     * 
     * @see measureSignalAngle for usage.
     * 
     */
    static constexpr float MIN_THRESHOLD_MEASUREMENTS = 0.10f;

    /**
     * @brief Delay after turning infrared LED in \p cumulateInfraredValues 
     *        on or off.
     * 
     * Needed for reliable infrared light.
     */
    static const int DELAY_IR_INTERACTION = 1000;
};

#endif // ECPSignalDetection_H
