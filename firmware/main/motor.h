#ifndef _MOTOR_H_
#define _MOTOR_H_
#include <stdbool.h>

/**
 *
 *  l298 Motor Driver
 *
 */
/**
 * MCPWM GPIO pins
 */
#define MOTOR_LEFT_PWM 7
#define MOTOR_RIGHT_PWM 8

/**
 * Init MCPWM signals on static pin numbers
 */
void mbot_motor_init_mcpwm(void);

/**
 * Direction GPIO pins
 */

#define MOTOR_LEFT_DDR_A 16
#define MOTOR_LEFT_DDR_B 15

#define MOTOR_RIGHT_DDR_A 18
#define MOTOR_RIGHT_DDR_B 17

/**
 * Init Direction signals on static pin numbers
 */
void mbot_motor_init_dir(void);

/**
 * Init PWM & Direction signals on static pin numbers
 */
void mbot_motor_init(void);

/**
 * Operate
 */

/**
 * Set the duty rate of the PWM A and B signals to both motors.
 *
 *
 * @param left  - Left motor speed,  ranges from 0.0 to 100.0
 * @param right - Right motor speed, ranges from 0.0 to 100.0
 *
 */
void mbot_motor_set_duty(float left, float right);

/**
 * Set the direction of the right motor
 */
void mbot_motor_set_dir_right(bool right);

/**
 * Set the direction of the left motor
 */
void mbot_motor_set_dir_left(bool left);

/**
 * Set the direction of the motors
 *
 * @param left  - Left motor direction
 * @param Right - Right motor direction
 */
void mbot_motor_set_dir(bool left, bool right);

/**
 * Stop the PWM signals
 */
void mbot_motor_stop(void);

#endif /* _MOTOR_H_ */
