#ifndef _MBOT_ACTIONS_
#define _MBOT_ACTIONS_

#define NONE 0x00

#ifndef _ESP_HTTP_SERVER_INC_
#define _ESP_HTTP_SERVER_INC_
#include <esp_http_server.h>
#endif /* _ESP_HTTP_SERVER_INC_ */

#define RESPONSE(buffer)          \
	ws_pkt->len = sizeof(buffer); \
	ws_pkt->payload = buffer;

typedef enum mbot_commad {
	NOP = 0x00,
	/**
	 * GPIO Control Instruction
	 * 
     * Arguments(1):
	 *  - Mode of the pin
	 *
	 * Example:
	 * 0x7F 0x03
	 */
	GPIO_CONTROL_MODE = 0x7F,
	/**
	 * GPIO Control Instruction
	 * 
     * Arguments(1):
	 *  - State of the Pin
	 *
	 * Example:
	 * 0x80 0x01
	 */
	GPIO_CONTROL_WRITE = 0x80,

	/**
	 * Motor Control Instruction
	 * 
     * Arguments(2):
	 *  - Left motor percentage from -100 to 100
	 *  - Right motor percentage from -100 to 100
	 *
	 * Example:
	 * 0xC0 -50 50
	 */
	MOTOR_CONTROL = 0xC0,

	/**
	 * Trigger Ultrasound 
	 * 
	 * Response(2):
	 * - MSByte of distance value
	 * - LSByte of distance value
     *
	 * Example:
	 * 0xDO
	 */
	SENSOR_ULTRASOUND = 0xD0
} mbot_commad_t;

typedef unsigned char mbot_command_arg_t;

void handle_motor_command(mbot_command_arg_t *args);

void mbot_handle_command(mbot_commad_t action, mbot_command_arg_t *args,
						 httpd_ws_frame_t *ws_pkt);

#endif
