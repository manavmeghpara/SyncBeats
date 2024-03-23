#ifndef UART_H
#define UART_H

#include <stdlib.h>
#include <stdint.h>
#include <termios.h>

//  Baud Rate
//  to change the baud rate, change value below to the relevant macro defined in termios header
#define BAUD_RATE 9600

int uart_init(const char* UART_DEVICE);
void uart_command(int uartFileDescriptor, const char* COMMAND, char* response, size_t maxSize);
void uart_read(int uartFileDescriptor, char* rx_buffer);
void uart_write(int uartFileDescriptor, uint8_t value);

#endif
