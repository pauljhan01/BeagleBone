#include "uart.h"

void init_comm(uart_config *config){
	config->tty_fd = open("/dev/ttyS4",O_RDWR | O_NOCTTY | O_SYNC);

	if(tcgetattr( config->tty_fd, &(config->tty))!=0){
		printf("Error");
	}

	memset(&(config->tty), 0, sizeof config->tty);
	cfsetospeed(&(config->tty), B115200);
	cfsetispeed(&(config->tty), B115200);

	config->tty.c_cflag = (config->tty.c_cflag & ~CSIZE) | CS8;
	config->tty.c_iflag &= ~IGNBRK;
	config->tty.c_lflag = 0;
	config->tty.c_oflag = 0;
	config->tty.c_cc[VMIN] = 0;
	config->tty.c_cc[VTIME] = 5;
	config->tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	config->tty.c_cflag |= (CLOCAL | CREAD);
	config->tty.c_cflag &= ~(PARENB | PARODD);
	config->tty.c_cflag &= ~CSTOPB;

	if( tcsetattr(config->tty_fd, TCSANOW, &(config->tty))!=0){
		printf("Error 2");
	}	
}

int main(){
	uart_config config;
	init_comm(&config);
	while(1){
		write(config.tty_fd, "hello!\n", 7);	
	}
	return 1;
}
