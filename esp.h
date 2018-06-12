#ifndef __ESP_H__
#define __ESP_H__

signed esp_init();
signed esp_mode(unsigned mode);
signed esp_connect(const char *ssid, const char *pwd);
signed esp_connection_mode(unsigned mode);
signed esp_checkip();
signed esp_listen(unsigned port);
void esp_tx(const char *payload);
unsigned int esp_rx(char buf[], unsigned len);
void zero(char buf[], unsigned len);

#endif
