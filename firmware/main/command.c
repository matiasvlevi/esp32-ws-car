#include "command.h"

#include <esp_http_server.h>

#include "driver/gpio.h"
#include <esp_log.h>
#include "motor.h"
#include "ultrasound.h"

static const char *TAG = "Command Interpreter";

void handle_motor_command(mbot_command_arg_t *args)
{
	int8_t motor_left = args[0];
	int8_t motor_right = args[1];

	printf("Motor args: %d %d\n", motor_left, motor_right);

	if (motor_left == 0 && motor_right == 0) {
		mbot_motor_set_duty(0.0, 0.0);
		mbot_motor_stop();
		return;
	}

	if (motor_left < 0) {
		motor_left = -motor_left;
		mbot_motor_set_dir_left(0);

		printf("Left is negative");
	} else {
		mbot_motor_set_dir_left(1);
	}

	// If sign bit on, motor goes backwars
	if (motor_right < 0) {
		motor_right = -motor_right;
		mbot_motor_set_dir_right(0);

		printf("Right is negative");
	} else {
		mbot_motor_set_dir_right(1);
	}

	mbot_motor_set_duty((float)motor_left, (float)motor_right);
}

void mbot_handle_command(mbot_commad_t command, mbot_command_arg_t *args,
						 httpd_ws_frame_t *ws_pkt)
{
	ESP_LOGI(TAG, "Recieved Command:  >>> %x", command);
	ESP_LOGI(TAG, "Recieved Command: Arguments: %x %x", args[0], args[1]);

	switch (command) {
		case NONE:
			break;

		case GPIO_CONTROL_MODE:
			if (!args[0]) args[0] = 12;

			if (!args[1]) args[1] = 0;

			gpio_reset_pin(args[0]);
			gpio_set_direction(args[0], args[1]);

			break;

		case GPIO_CONTROL_WRITE:
			if (!args[0]) args[0] = 12;

			gpio_set_level(args[0], args[1]);

			break;

		case SENSOR_ULTRASOUND:
			float distance = mbot_ultrasound_read();
			printf("Distance = %f cm", distance);

			ws_pkt->payload[0] = (int16_t)distance & 0xFF,
			ws_pkt->payload[1] = ((int16_t)distance) >> 8 & 0xFF,
			ws_pkt->len = 2;

			break;

		case MOTOR_CONTROL:
			handle_motor_command(args);

			break;
	}
}
