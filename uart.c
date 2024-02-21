#include "uart.h"

void init_comm(uart_config *config){
	config->tty_fd = open("/dev/ttyS4",O_RDWR | O_NOCTTY);

	if(tcgetattr( config->tty_fd, &(config->tty))!=0){
		printf("Error");
	}

	memset(&(config->tty), 0, sizeof config->tty);
	cfsetospeed(&(config->tty), (speed_t)115200);
	cfsetispeed(&(config->tty), (speed_t)115200);

	config->tty.c_cc[VMIN] = 1;
	config->tty.c_cc[VTIME] = 5;
	config->tty.c_cflag |= CREAD | CLOCAL;

	/*
	 * termios->c_cflag &= ~(CSIZE | PARENB);
	 * termios->c_cflag |= CS8;
	 * */
	cfmakeraw(&(config->tty)); 

	tcflush(config->tty_fd, TCIFLUSH);

	if( tcsetattr(config->tty_fd, TCSANOW, &(config->tty))!=0){
		printf("Error 2");
	}
	
}

int main(){
	uart_config config;
	init_comm(&config);
	int n_written = 0;
	unsigned char cmd[] = "INIT\n";
	while(1){
		n_written = write(config.tty_fd, &cmd, sizeof(cmd)-1);	
		printf("%d bytes written\n",n_written);
	}
	return 1;
}
