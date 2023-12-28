#include "ultrasound.h"

#include <driver/gpio.h>
#include <driver/timer.h>
#include <rom/ets_sys.h>

void mbot_ultrasound_init(void)
{
	// Set trigger as output
	gpio_reset_pin(ULTRASOUND_TRIG_PIN);
	gpio_set_direction(ULTRASOUND_TRIG_PIN, GPIO_MODE_OUTPUT);

	// Set echo as input
	gpio_reset_pin(ULTRASOUND_ECHO_PIN);
	gpio_set_direction(ULTRASOUND_ECHO_PIN, GPIO_MODE_INPUT);

	gpio_set_level(ULTRASOUND_TRIG_PIN, 0);

	mbot_ultrasound_init_timer();
}

void mbot_ultrasound_init_timer(void)
{
	timer_config_t config = {.divider = 80,
							 .counter_dir = TIMER_COUNT_UP,
							 .counter_en = TIMER_PAUSE,
							 .alarm_en = TIMER_ALARM_DIS,
							 .auto_reload = TIMER_AUTORELOAD_DIS};

	timer_init(TIMER_GROUP_0, TIMER_1, &config);
}

void mbot_ultrasound_timer_start()
{
	timer_set_counter_value(TIMER_GROUP_0, TIMER_1, 0);

	timer_start(TIMER_GROUP_0, TIMER_1);
}

void mbot_ultrasound_timer_read(uint64_t *value)
{
	timer_get_counter_value(TIMER_GROUP_0, TIMER_1, value);
}

float mbot_ultrasound_read(void)
{
	gpio_set_level(ULTRASOUND_TRIG_PIN, 0);

	ets_delay_us(4);

	gpio_set_level(ULTRASOUND_TRIG_PIN, 1);

	ets_delay_us(4);

	gpio_set_level(ULTRASOUND_TRIG_PIN, 0);

	// Wait for ECHO rising edge
	while (!gpio_get_level(ULTRASOUND_ECHO_PIN))
		;

	mbot_ultrasound_timer_start();

	// Wait for ECHO falling edge
	while (gpio_get_level(ULTRASOUND_ECHO_PIN))
		;

	uint64_t value = 0;
	mbot_ultrasound_timer_read(&value);

	return value / 58.2;
}
