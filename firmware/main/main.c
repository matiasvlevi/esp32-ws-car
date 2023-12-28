
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>

#include "./motor.h"
#include "./ultrasound.h"
#include "./wifi.h"

#include "webserver.h"

static const char *TAG = "ESP32-CAR";

/**
 * ENTRYPOINT
 */
void app_main(void)
{
	ESP_ERROR_CHECK(init_nvram());

	mbot_motor_init();

	mbot_ultrasound_init();

	init_wifi();

    init_webserver();
}
