#include "hal/bluetooth.h"
#include "hal/uart.h"
#include "stdbool.h"
#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS4"
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

int charToInt(char c) {
    // Check if the character is between '0' and '9'
    if(c >= '0' && c <= '9') {
        // Subtract '0' to convert to int
        return c - '0';
    } else {
        // Return -1 or some error code if not a digit
        return -1;
    }
}

void* readDataFromBle(void* fd){
    int uartFileDescriptor = *((int*)fd);
    //char* rx_buffer = malloc(sizeof(*rx_buffer));
    char rx_buffer; 
	printf("Thread 1 Reading...\n");

    while(1){
        // uart_read(uartFileDescriptor, rx_buffer);
        int bytesRead = read(uartFileDescriptor, &rx_buffer, 1);
        if (bytesRead < 0) {
            perror("Error occurred while reading UART device file");
        }else{
            printf("%c\n", rx_buffer);
            if( rx_buffer >= '0' && rx_buffer <= '9' ){
        
                enum commands c = charToInt(rx_buffer);

                switch(c){
                case Play:{
                    printf("Play\n");
                }
                break; 
                case Stop:{
                    printf("Stop\n");	
                }
                    break;
                case Vol_UP:{
                    printf("V Up\n");
                }
                    break;
                case Vol_DOWN:{
                    printf("V Down\n");
                
                }
                default:
                break;

                }
            }
            
        }
        sleepForMs(50); 
    }
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
