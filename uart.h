#ifndef UART_H
#define UART_H
#include "termios.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"

typedef struct uart_config{
	struct termios tty;
	int tty_fd;
}uart_config;

void init_comm(struct uart_config * config);

void receive_message();

void send_message();

#endif
