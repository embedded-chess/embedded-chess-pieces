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
#include <EmbeddedChessPieces.h>

#define FORWARD_TIME 750
#define MOVEMENT_BREAK 375

#define DEFAULT_MOVEMENT_CALIBRATION 3900

class ECPMovement {
public:
    /**
     * @brief Construct a new movement object.
     * 
     * @param d Dezibot to move
     * @param mc Base value to calibrate the dezibot's movement (default 3900)
     */
    ECPMovement(Dezibot &d, uint mc);

    /**
     * @brief Move chess piece given number of fields forward.
     * 
     * @param numberOfFields Number of fields the dezibot should move forward
     */
    void move(uint numberOfFields);

    /**
     * @brief Turn 90 degrees left.
     * 
     */
    void turnLeft();

    /**
     * @brief Turn 90 degrees right.
     * 
     */
    void turnRight();

protected:
    Dezibot &dezibot;
    ECPColorDetection ecpColorDetection;

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
};

#endif // ECPMovement_h
