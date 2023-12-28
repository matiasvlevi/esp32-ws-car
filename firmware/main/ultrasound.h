#ifndef _ULTRASOUND_H_
#define _ULTRASOUND_H_

#include <stdint.h>

/**
 * HC-SR04 Pins
 */
#define ULTRASOUND_TRIG_PIN 13
#define ULTRASOUND_ECHO_PIN 14

void mbot_ultrasound_init_timer(void);

void mbot_ultrasound_timer_start();

/**
 * Init the ultrasound hardware
 */
void mbot_ultrasound_init(void);

void mbot_ultrasound_timer_read(uint64_t *value);

/**
 * Read the distance from the ultrasound
 * 
 * @return The distance read from the ultrasound sensor 
 */
float mbot_ultrasound_read(void);

#endif /* _ULTRASOUND_H_ */
