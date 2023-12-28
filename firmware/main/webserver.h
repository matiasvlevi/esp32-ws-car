#ifndef _WEBSERVER_
#define _WEBSERVER_


#ifndef _ESP_HTTP_SERVER_INC_
#define _ESP_HTTP_SERVER_INC_
#include <esp_http_server.h>
#endif /* _ESP_HTTP_SERVER_INC_ */

#define NFREE(v) \
	free(v); \
	v = NULL;


/*
 * Structure holding server handle
 * and internal socket fd in order
 * to use out of request send
 */
struct async_resp_arg {
	httpd_handle_t hd;
	int fd;
};

/**
 * Clear cache
 * 
 * @return esp_err_t 
 */
esp_err_t init_nvram(void);

/*
 * Start the webserver
 */
void init_webserver(void);

#endif /* _WEBSERVER_ */