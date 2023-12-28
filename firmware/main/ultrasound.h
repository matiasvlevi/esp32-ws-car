#ifndef _ULTRASOUND_H_
#define _ULTRASOUND_H_

#include <stdint.h>

#define ULTRASOUND_TRIG_PIN 13
#define ULTRASOUND_ECHO_PIN 14

void mbot_ultrasound_init(void);

void mbot_ultrasound_init_timer(void);

void mbot_ultrasound_timer_start();

void mbot_ultrasound_timer_read(uint64_t *value);

float mbot_ultrasound_read(void);

#endif /* _ULTRASOUND_H_ */
