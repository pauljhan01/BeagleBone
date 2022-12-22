#include "uart.h"

void init_comm(uart_config *config){
	config->tty_fd = open("/dev/ttyS4",O_RDWR | O_NONBLOCK | O_NONBLOCK | O_NOCTTY);
	memset(&(config->tty), 0, sizeof config->tty);
	cfsetospeed(&(config->tty), (speed_t)115200);
	
}

int main(){
	uart_config config;
	init_comm(&config);
	while(1){

	}
	return 1;
}
