#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "hal/uart.h"

int uart_init(const char* UART_DEVICE)
{
    int uartFileDescriptor = open(UART_DEVICE, O_RDWR);
    if (uartFileDescriptor < 0) {
        perror("Unable to open UART device");
        return -1;
    }

    struct termios tty;

    // Set serial port parameters
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(uartFileDescriptor, &tty) != 0) {
        perror("Error getting serial port attributes");
        close(uartFileDescriptor);
        return -1;
    }

    cfsetospeed(&tty, BAUD_RATE);
    cfsetispeed(&tty, BAUD_RATE);
    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // 8 data bits
    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CRTSCTS; // Disable hardware flow control
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_oflag &= ~OPOST; // Raw output
    tty.c_cc[VMIN] = 1; // Read at least 1 character 
    tty.c_cc[VTIME] = 5; // Timeout in 0.5 seconds

    if (tcsetattr(uartFileDescriptor, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        close(uartFileDescriptor);
        return -1;
    }

    return uartFileDescriptor;
}

void uart_command(int uartFileDescriptor, const char* COMMAND, char* response, size_t maxSize)
{
    if (write(uartFileDescriptor, COMMAND, strlen(COMMAND)) < 0) {
        perror("Error executing UART command");
        return;
    }

    int numBytesRead = read(uartFileDescriptor, response, maxSize);
    if (numBytesRead < 0) {
        perror("Error reading from UART port");
        return;
    }

    response[numBytesRead] = '\0';
}

void uart_read(int uartFileDescriptor, char* rx_buffer)
{
    int bytesRead = read(uartFileDescriptor, rx_buffer, 1024);
    printf("%s\n", rx_buffer);
    if (bytesRead < 0) {
        perror("Error occurred while reading UART device file");
    }
}

void uart_write(int uartFileDescriptor, uint8_t value)
{
    int bytesWritten = write(uartFileDescriptor, &value, 1);
    if (bytesWritten < 0) {
        perror("An error occurred while writing to the UART device file");
    }
}
