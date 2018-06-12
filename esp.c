#include "esp.h"
#include "str.h"
#include "uart.h"
#include "printf.h"

signed esp_init() {
	const char *payload = "AT\r\n";
	char buf[4096];
	signed try = 0;
	while(1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK")) {
			break;
		}
		try++;
	}
	return try;
}

signed esp_mode(unsigned mode) {
	char *payload = "AT+CWMODE=1\r\n";
	switch(mode) {
		case 0:
			payload = "AT+CWMODE=0\r\n";
			break;
		case 1:
			break;
		case 2: 
			payload = "AT+CWMODE=2\r\n";
			break;
		default: 
		break;
	}	
	char buf[4096];
	unsigned try = 0;
	while(1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK") || strstr(buf, "ready")) {
			break;
		}
		try++;
	}
	return try;
}

signed esp_connect(const char *ssid, const char *pwd) {
	char payload[2048];
	char buf[4096];
	snprintf(payload, sizeof(payload), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pwd);	
	unsigned try = 0;
	while (1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK") || strstr(buf, "WIFI CONNECTED")) break;
		try++;
	}
	return try;
}

signed esp_connection_mode(unsigned mode) {
	char *payload = "AT+CIPMUX=1\r\n";
	switch(mode) {
		case 0:
			payload = "AT+CIPMUX=0\r\n";
			break;
		case 1:
			break;
		case 2: 
			payload = "AT+CIPMUX=2\r\n";
			break;
		default: 
		break;
	}
	char buf[4096];
	unsigned try = 0;
	while(1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK")) {
			break;
		}
		try++;
	}
	return try;
}

signed esp_checkip() {
	const char *payload = "AT+CIFSR\r\n";
	char buf[4096];
	signed try = 0;
	while(1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK") || strstr(buf, "WIFI CONNECTED")) {
			break;
		}
		try++;
	}
	return try;
}

signed esp_listen(unsigned port) {
	char payload[512];
	char buf[4096];
	snprintf(payload, sizeof(payload), "AT+CIPSERVER=1,%d\r\n", port);	
	unsigned try = 0;
	while (1) {
		zero(buf, sizeof(buf));
		esp_tx(payload);
		esp_rx(buf, sizeof(buf));
		if (strstr(buf, "OK")) break;
		try++;
	}
	return try;
}

void esp_tx(const char *payload) {
	for (unsigned i = 0; i < strlen(payload); i++) {
		uart_putc((unsigned int) payload[i]);
	}
	uart_flush();
}

unsigned int esp_rx(char buf[], unsigned buflen) {
	unsigned bytes;
	for (bytes = 0; uart_rx_has_data() && (bytes < buflen); bytes++) {
		buf[bytes] = uart_getc();
	}
	buf[bytes] = '\0';
	return bytes;
}

void zero(char buf[], unsigned len) {
	for (unsigned i = 0; i < len; i++) {
		buf[i] = '\0';
	}
}
