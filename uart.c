#include "uart.h"

enum UART_Mapping{
	UART_1 = 4,
	UART_4 = 6,
	UART_5 = 7,
	UART_6 = 8
};

static uart_config uart[4];

const char * data_file_name = "/home/debian/BeagleBone/voltage_data.csv";

void init_comm(uart_config *config, int uart_mapping){
	char uart_path[20];
	char uart_file_num[5];
	sprintf(uart_file_num, "%d", uart_mapping);
	strcpy(uart_path, "/dev/ttyS");
	strcat(uart_path, uart_file_num);
	config->tty_fd = open(uart_path, O_RDWR | O_NOCTTY | O_SYNC);

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
/*
 * Four voltage sensing boards with electrodes attached
 */
#define num_boards 4
void send_and_receive(){
	FILE * data_file = fopen(data_file_name, "a");
	time_t run_for_seconds = 5;	
	char data_buf[100];
	for(int i = 0; i < num_boards; i++){
		char command[20];
		sprintf(command, "BEGIN %d\n", i);
		write(uart[i].tty_fd, command, 8);
		time_t start_time = time(NULL);
		while(time(NULL) - start_time < run_for_seconds){
			read(uart[i].tty_fd, data_buf, sizeof data_buf);
			strcat(data_buf, ","); //to make csv
			fprintf(data_file, "%s", data_buf);
		}
	}		
	fclose(data_file);
};

int main(){
	init_comm(&uart[0], UART_1);
	init_comm(&uart[1], UART_4);
	init_comm(&uart[2], UART_5);
	init_comm(&uart[3], UART_6);
	send_and_receive();
	return 1;
}
