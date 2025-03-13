/**
 * @file ECPMovement.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper class for chess piece movement.
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ECPMovement_h
#define ECPMovement_h

#include <Dezibot.h>

#include "ECPChessLogic/ECPChessField.h"
#include <ECPColorDetection/ECPColorDetection.h>
#include <ECPSignalDetection/ECPSignalDetection.h>

#define FORWARD_TIME 750
#define MOVEMENT_BREAK 375
#define ROTATION_SPEED 8192
#define ROTATION_CORRECTION_TIME 10000
#define DEFAULT_MOVEMENT_CALIBRATION 3900
#define MEASURING_DELAY 5

class ECPMovement {
public:
    /**
     * @brief Construct a new movement object.
     * 
     * @param dezibot Dezibot to move
     * @param movementCalibration Base value to calibrate the dezibot's movement (default 3900)
     */
    ECPMovement(
        Dezibot &dezibot,
        uint movementCalibration = DEFAULT_MOVEMENT_CALIBRATION
    );

    /**
     * @brief Move chess piece given number of fields forward.
     * 
     * @param numberOfFields Number of fields the dezibot should move forward
     */
    void move(uint numberOfFields);

    /**
     * @brief Turn 90 degrees left.
     * 
     * @param currentField field of the dezibot
     * @param intendedDirection direction the dezibot should look at after rotation
     * 
     * @details Uses \p ECPSignalDetection::measureDezibotAngle internally to
     *          rotate dezibot to the correct angle. Make sure to place a
     *          dezibot running <tt>examples/ir_emitter.ino</tt> within reach!
     */
    void turnLeft(ECPChessField currentField, ECPDirection intendedDirection);

    /**
     * @brief Turn 90 degrees right.
     * 
     * @param currentField field of the dezibot
     * @param intendedDirection direction the dezibot should look at after rotation
     * 
     * @details Uses \p ECPSignalDetection::measureDezibotAngle internally to
     *          rotate dezibot to the correct angle. Make sure to place a
     *          dezibot running <tt>examples/ir_emitter.ino</tt> within reach!
     */
    void turnRight(ECPChessField currentField, ECPDirection intendedDirection);

protected:
    Dezibot &dezibot;
    ECPColorDetection ecpColorDetection;
    ECPSignalDetection ecpSignalDetection;

    /**
     * @brief Value to calibrate movement.
     * 
     * If the Dezibot is not moving forward at all increasing the value may help.
     * If the robot is just jumping up and down but not forward, try a lower value.
     */
    const uint movementCalibration;

private:
    /**
     * @brief Move straight for the given amount of time.
     * 
     * To minimize drift, a break is implemented after each movement.
     * 
     * @param timeMovement in ms - how long the dezibot should move.
     * @param timeBreak in ms - how long the dezibot should pause.
     */
    void moveForward(int timeMovement, int timeBreak);

    /**
     * @brief Move straight to the next field.
     * 
     * Default interval of movement before checking the field color
     * is defined in MOVEMENT_TIME and MOVEMENT_BREAK.
     */
    void moveToNextField();

    /**
     * Print request to correct dezibot on the board after faulty rotation
     * 
     * The user has 10 seconds to correct the position and direction of the dezibot
     * 
     * @param currentField Field of the dezibot
     * @param intendedDirection Direction the dezibot should look at after rotation
     */
    void displayRotionCorrectionRequest(
        ECPChessField currentField, 
        ECPDirection intendedDirection
    );

    /**
     * @brief Rotate dezibot from measured initial angle to specified goal angle.
     * 
     * This function uses an incremental approach. Based on the difference of
     * the two angles, incrementally rotate the bot toward the goal, considering
     * the tolerance specified in \p ROTATION_TOLERANCE.
     * 
     * If the rotation could not be completed successfully after a certain
     * amount of iterations (cf. \p MAX_ROTATION_ITERATIONS), return \p false.
     * 
     * @param goalAngle The target angle to which the dezibot is to be rotated.
     * @param initialAngle Measured initial angle of the dezibot, see
     *                     \p EcpSignalDetection::measureDezibotAngle.
     * 
     * @return bool true if rotation was successful, false otherwise
     * 
     * @see calculateRotationTime() for details on how the rotation time is computed.
     * @see rotateLeft and \p rotateRight for the actual rotation implementations.
     * @see EcpSignalDetection::measureDezibotAngle for how the current angle is measured.
     */
    bool rotateToAngle(int goalAngle, int initialAngle);

    /**
     * @brief Rotate dezibot to the left (counter-clockwise) for a specified duration.
     * 
     * @param movementTime Duration for which the bot should rotate left in
     *                     milliseconds.
     * 
     * @details Use right motor of the dezibot (<tt>dezibot.motion.right<\tt>).
     */
    void rotateLeft(uint movementTime);

    /**
     * @brief Rotate dezibot to the right (clockwise) for a specified duration.
     * 
     * @param movementTime Duration for which the bot should rotate right in
     *                     milliseconds.
     * 
     * @details Use left motor of the dezibot (<tt>dezibot.motion.left</tt>).
     */
    void rotateRight(uint movementTime);

    /**
     * @brief Calculate the time required to rotate based on the angle difference.
     * 
     * Compute the rotation time needed to adjust the dezibot's angle based on
     * the difference between the current angle and the target angle.
     *
     * @param normalizedAngleDifference Difference in angle between the current
     *            and target positions, in degrees, normalized to [-180, 180].
     *
     * @return uint Calculated rotation time (in milliseconds) rounded to the
     *              nearest integer.
     * 
     * @details The rotation time is derived using a linear relationship. It is
     *          assumed that a 180° rotation takes about 5000 milliseconds
     *          Therefore, the angle is multiplied by 28 which approximates this
     *          assumption (180° * 28 = 5040 ms).
     * 
     * @see rotateToAngle for how this function is used in the context of
     *      rotating the dezibot to a specific angle.
     * @see ROTATION_TIME_FACTOR for factor used to define linear relationship.
     */
    uint calculateRotationTime(int normalizedAngleDifference);

    /**
     * @brief Tolerance for a rotation to be accepted in degrees.
     * 
     * For example, if the initial infrared signal was 0°, then everything
     * in [-3°, 3°] will be accepted as an successful rotation.
     * This is necessary to avoid unnecessary loops, e.g. if the infrared
     * emitting dezibot is too far away.
     * 
     * @see rotateToAngle for usage.
     */
    static const int ROTATION_TOLERANCE = 3;

    /**
     * @brief Maximum rotation iterations used in \p turnLeft and \p turnRight.
     * 
     * @see rotateToAngle for usage.
     * 
     */
    static const size_t MAX_ROTATION_ITERATIONS = 20;

    /**
     * @brief Factor used to calculate rotation time.
     * 
     * @see calculateRotationTime for usage.
     * 
     */
    static constexpr float ROTATION_TIME_FACTOR = 28;
};

#endif // ECPMovement_h
