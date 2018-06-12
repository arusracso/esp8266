#include "esp.h"
#include "uart.h"
#include "gpio.h"
#include "rpi.h"
#include "str.h"

void flicker2(unsigned pin, unsigned delay, unsigned delay2) {
	delay_ms(delay);
	gpio_write(pin, 1);
	delay_ms(delay2);
	gpio_write(pin, 0);
}

void flicker(unsigned pin) {
	flicker2(pin, 1000, 3000);
}

void notmain(void) {	
	unsigned green = GPIO_PIN16;
	unsigned blue = GPIO_PIN20;
	unsigned red = GPIO_PIN21;
	uart_init();
	gpio_set_output(green);
	gpio_set_output(blue);
	gpio_set_output(red);
	gpio_write(green, 1);
	gpio_write(blue, 1);
	gpio_write(red, 1);
	delay_ms(1000);
	gpio_write(green, 0);
	gpio_write(blue, 0);
	gpio_write(red, 0);

	const char *SSID = "WiPi";
	const char *PWD = "WiPi1234";
	
	while (1) {
		signed ret_init = esp_init(); 
			assert(ret_init >= 0);
			flicker(green);
		signed ret_mode = esp_mode(1);	
			assert(ret_mode >= 0);
			flicker(blue);
		signed ret_connect = esp_connect(SSID, PWD);	
			assert(ret_connect >= 0);
			flicker(red);
		signed ret_ip = esp_checkip();
			assert(ret_ip >= 0);
			flicker(green);
		signed ret_client = esp_connection_mode(1); //multi connection
			flicker(blue);
		signed ret_socket = esp_listen(80); //listen on port 80
			flicker(red);
	}	
}
