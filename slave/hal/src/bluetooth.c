#include "hal/bluetooth.h"
#include "hal/uart.h"
#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS2"
static pthread_t readTid;
static int fd; 

void bluetooth_init(){
	fd = uart_init(UART_DEVICE);
	pthread_create(&readTid, NULL, readDataFromBle, (void*)&fd);
}


void bluetooth_cleanup(){
	pthread_cancel(readTid); 
	pthread_join(readTid, NULL);
    close(fd);
}

void* readDataFromBle(void* fd){
    int uartFileDescriptor = *((int*)fd);
    // char* rx_buffer = malloc(sizeof(*rx_buffer));
    char rx_buffer; 
	printf("Thread 1 Reading...\n");

    while(1){
        // uart_read(uartFileDescriptor, rx_buffer);
        int bytesRead = read(uartFileDescriptor, &rx_buffer, 1);
        if (bytesRead < 0) {
            perror("Error occurred while reading UART device file");
        }else{
            printf("%c\n", rx_buffer);
        }
        sleepForMs(50); 
    }
    // free(rx_buffer);
}

void sleepForMs(long long delayInMs){
    const long long NS_PER_MS = 1000 * 1000; 
    const long long NS_PER_SECOND = 1000000000;
    
    long long delayNs = delayInMs * NS_PER_MS; 
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND; 

    struct timespec reqDelay = {seconds, nanoseconds}; 
    nanosleep(&reqDelay, (struct timespec *) NULL);

}
