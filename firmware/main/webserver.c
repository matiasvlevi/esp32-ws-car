#include "./webserver.h"


#include "./command.h"
#include "./motor.h"

#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <unistd.h>
#include "esp_eth.h"
#include "esp_netif.h"

static const char *TAG = "WEBSERVER";

static esp_err_t echo_handler(httpd_req_t *req)
{
	if (req->method == HTTP_GET) {
		ESP_LOGI(TAG, "Handshake done, the new connection was opened");
		return ESP_OK;
	}

	uint8_t ws_data[8];

	httpd_ws_frame_t ws_pkt = {
		.type = HTTPD_WS_TYPE_TEXT,
		.payload = ws_data
	};

	// Get the frame
	esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 8);

	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame with length 8: %d",
				 ret);
		return ret;
	}

	// Update last command

	ESP_LOGI(TAG, "frame len is %d", ws_pkt.len);
	ESP_LOGI(TAG, "Got packet with message: %s", ws_pkt.payload);
	ESP_LOGI(TAG, "Packet type: %d", ws_pkt.type);

	// Cast 1st Byte as Command Byte
	mbot_commad_t command = ws_pkt.payload[0];

	uint8_t args[2];
	args[0] = ws_pkt.payload[1];
	args[1] = ws_pkt.payload[2];

	mbot_handle_command(command, args, &ws_pkt);

	if (ws_pkt.len == 0) {
		uint8_t r[] = "Ok";
		ws_pkt.payload = r;
		ws_pkt.len = 2;
	}

	ret = httpd_ws_send_frame(req, &ws_pkt);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
	}

	return ret;
}

static const httpd_uri_t ws = {.uri = "/ws",
							   .method = HTTP_GET,
							   .handler = echo_handler,
							   .user_ctx = NULL,
							   .is_websocket = true};

static httpd_handle_t start_webserver(void)
{
	httpd_handle_t server = NULL;
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	config.lru_purge_enable = true;

	// Start the httpd server
	ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
	if (httpd_start(&server, &config) == ESP_OK) {
		// Registering the ws handler
		ESP_LOGI(TAG, "Registering URI handlers");
		httpd_register_uri_handler(server, &ws);
		return server;
	}

	ESP_LOGI(TAG, "Error starting server!");
	return NULL;
}

static void stop_webserver(httpd_handle_t server)
{
	// Stop the httpd server
	httpd_stop(server);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
							   int32_t event_id, void *event_data)
{
	httpd_handle_t *server = (httpd_handle_t *)arg;
	if (*server) {
		ESP_LOGI(TAG, "Lost connection...");

		//
		stop_webserver(*server);
		*server = NULL;
	}

	// Stop motors
	mbot_motor_set_duty(0.0, 0.0);
	mbot_motor_stop();
}

static void connect_handler(void *arg, esp_event_base_t event_base,
							int32_t event_id, void *event_data)
{
	httpd_handle_t *server = (httpd_handle_t *)arg;
	if (*server == NULL) {
		ESP_LOGI(TAG, "Starting webserver");
		*server = start_webserver();
	}
}

esp_err_t init_nvram(void)
{
	// Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
		ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	return (ret);
}

void init_webserver(void)
{
	static httpd_handle_t server = NULL;

	ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
											   &connect_handler, &server));
	ESP_ERROR_CHECK(esp_event_handler_register(
		WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

	server = start_webserver();

}
