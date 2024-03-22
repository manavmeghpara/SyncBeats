#include "hal/uart.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS1"

void* readDataFromBle(void* fd)
{
    int uartFileDescriptor = *((int*)fd);
    uint8_t* rx_buffer = malloc(sizeof(*rx_buffer));
	printf("Thread 1 Reading...\n");
    uart_read(uartFileDescriptor, rx_buffer, 1);
    printf("Read value of %d from Ble\n", rx_buffer[0]);
    free(rx_buffer);
    pthread_exit(NULL);
}

void* writeToBle(void* fd)
{
    int uartFileDescriptor = *((int*)fd);
	printf("Thread 2 Writing 0xFE\n");
    uart_write(uartFileDescriptor, 0xFE);
    pthread_exit(NULL);
}

int main()
{
    int fd = uart_init(UART_DEVICE);

    pthread_t readTid;
    pthread_t writeTid;

    pthread_create(&readTid, NULL, readDataFromBle, (void*)&fd);
    pthread_create(&writeTid, NULL, writeToBle, (void*)&fd);
    while(1);
    pthread_join(readTid, NULL);
    pthread_join(writeTid, NULL);

    close(fd);
    return 0;
}
