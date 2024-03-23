#include "hal/uart.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS2"

void* readDataFromBle(void* fd)
{
    int uartFileDescriptor = *((int*)fd);
	printf("Thread 1 Reading...\n");
    char byte [1024];
    while(1){
        int bytesRead = read(uartFileDescriptor, &byte, 1024);
        printf("%s\n", byte);
        if (bytesRead < 0) {
            perror("Error occurred while reading UART device file");
        }
    }
    pthread_exit(NULL);
}

void* writeToBle(void* fd)
{
    int uartFileDescriptor = *((int*)fd);
	printf("Thread 2 Writing 0xFE\n");
    // uart_write(uartFileDescriptor, 0xFE);
    char byte[1024] = "writing";  
    int bytesWritten = write(uartFileDescriptor, &byte, 1);
    if (bytesWritten < 0) {
        perror("An error occurred while writing to the UART device file");
    }
    printf("wrote to phone\n"); 
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

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <fcntl.h>
// #include <errno.h>

// #define DEVICE_FILE "/dev/ttyS2"

// void *read_from_serial(void *arg) {
//     int fd;
//     char buffer[1024]; // Adjust buffer size as needed

//     // Open the serial port file for reading
//     fd = open(DEVICE_FILE, O_RDONLY);
//     if (fd == -1) {
//         perror("Failed to open serial port");
//         pthread_exit(NULL);
//     }

//     // Continuously read from the serial port and print the data
//     while (1) {
//         ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
//         if (bytes_read == -1) {
//             perror("Error reading from serial port");
//             close(fd);
//             pthread_exit(NULL);
//         } else if (bytes_read > 0) {
//             // Print the read data to the screen
//             printf("From Bluetooth : %s", buffer);
//         }
//     }

//     // Close the serial port file
//     close(fd);

//     return NULL;
// }

// int main() {
//     pthread_t tid;

//     // Create a thread for reading from the serial port
//     if (pthread_create(&tid, NULL, read_from_serial, NULL) != 0) {
//         perror("Failed to create thread");
//         return EXIT_FAILURE;
//     }

//     // Main thread continues execution
//     // You can add additional code here if needed
//     while(1);
//     // Wait for the thread to terminate (this won't happen in this example)
//     pthread_join(tid, NULL);

//     return EXIT_SUCCESS;
// }
