#include "motor.h"

#include <esp_log.h>

#include "driver/gpio.h"
#include "driver/mcpwm.h"

void mbot_motor_init_mcpwm(void)
{
	ESP_ERROR_CHECK(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, MOTOR_RIGHT_PWM));
	ESP_ERROR_CHECK(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, MOTOR_LEFT_PWM));

	mcpwm_config_t pwm_config;
	pwm_config.frequency = 1000;  // Frequency of PWMxA
	pwm_config.cmpr_a = 0;		  // Duty cycle of PWMxA
	pwm_config.cmpr_b = 0;		  // Duty cycle of PWMxB
	pwm_config.counter_mode = MCPWM_UP_COUNTER;
	pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

	// Set the configurations
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
}

void mbot_motor_set_dir_right(bool right)
{
	gpio_set_level(MOTOR_RIGHT_DDR_A, right);
	gpio_set_level(MOTOR_RIGHT_DDR_B, !right);
}

void mbot_motor_set_dir_left(bool left)
{
	gpio_set_level(MOTOR_LEFT_DDR_A, left);
	gpio_set_level(MOTOR_LEFT_DDR_B, !left);
}

void mbot_motor_set_dir(bool left, bool right)
{
	mbot_motor_set_dir_right(right);
	mbot_motor_set_dir_left(left);
}

void mbot_motor_init_dir(void)
{
	gpio_reset_pin(MOTOR_RIGHT_DDR_A);
	gpio_set_direction(MOTOR_RIGHT_DDR_A, GPIO_MODE_OUTPUT);

	gpio_reset_pin(MOTOR_RIGHT_DDR_B);
	gpio_set_direction(MOTOR_RIGHT_DDR_B, GPIO_MODE_OUTPUT);

	gpio_reset_pin(MOTOR_LEFT_DDR_A);
	gpio_set_direction(MOTOR_LEFT_DDR_A, GPIO_MODE_OUTPUT);

	gpio_reset_pin(MOTOR_LEFT_DDR_B);
	gpio_set_direction(MOTOR_LEFT_DDR_B, GPIO_MODE_OUTPUT);

	gpio_set_level(MOTOR_RIGHT_DDR_A, 0);
	gpio_set_level(MOTOR_LEFT_DDR_A, 0);
	gpio_set_level(MOTOR_RIGHT_DDR_B, 0);
	gpio_set_level(MOTOR_LEFT_DDR_B, 0);
}

void mbot_motor_init(void)
{
	mbot_motor_init_mcpwm();
	mbot_motor_init_dir();
}

void mbot_motor_set_duty(float left, float right)
{
	printf("Motor %.2f %.2f\n", left, right);
	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, left);
	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, right);

	// Start MCPWM unit 0 on both signals
	mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}

void mbot_motor_stop(void)
{
	gpio_set_level(MOTOR_RIGHT_DDR_A, 0);
	gpio_set_level(MOTOR_LEFT_DDR_A, 0);
	gpio_set_level(MOTOR_RIGHT_DDR_B, 0);
	gpio_set_level(MOTOR_LEFT_DDR_B, 0);

	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
}
