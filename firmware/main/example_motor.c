#include "example_motor.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"

void motor_example()
{
	mbot_motor_init();
	mbot_motor_set_duty(0, 0);

	vTaskDelay(2000 / portTICK_PERIOD_MS);

	for (int i = 0; i < 2; i++) {
		mbot_motor_set_duty(100, 100);

		vTaskDelay(1000 / portTICK_PERIOD_MS);

		if (i % 2)
			mbot_motor_set_duty(0, 100);
		else
			mbot_motor_set_duty(100, 0);

		vTaskDelay(650 / portTICK_PERIOD_MS);

		mbot_motor_set_duty(45, 45);

		vTaskDelay(650 / portTICK_PERIOD_MS);
	}

	mbot_motor_set_duty(100, 100);

	vTaskDelay(800 / portTICK_PERIOD_MS);

	mbot_motor_set_duty(0, 100);

	vTaskDelay(3500 / portTICK_PERIOD_MS);

	mbot_motor_set_duty(0, 0);
	mbot_motor_stop();

	while (true) {
		vTaskDelay(1);
	}
}
