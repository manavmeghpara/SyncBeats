#include "hal/bluetooth.h"
#include "hal/joystick_control.h"
#include "hal/util.h"

#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS2"
static pthread_t writeTid;
static int fd; 

void bluetooth_init(){
	fd = uart_init(UART_DEVICE);
	pthread_create(&writeTid, NULL, writeToBle, (void*)&fd);
}


void bluetooth_cleanup(){
	pthread_cancel(writeTid); 
	pthread_join(writeTid, NULL);
    close(fd);
}

void* writeToBle(void* fd){
    int uartFileDescriptor = *((int*)fd);
	printf("Thread 2 Writing 0xFE\n");
	while(1){
		int bytesWritten = -1; 
		enum eJoystickDirections direction = getDirections(); 
		switch(direction){
			case Left:{
				 bytesWritten = write(uartFileDescriptor, "Left\n", sizeof("Left\n"));
			}
			break; 
			case Right:{
				 bytesWritten = write(uartFileDescriptor, "Right\n", sizeof("Right\n"));
			}
				break;
			case Up:{
				 bytesWritten = write(uartFileDescriptor, "Up\n", sizeof("Up\n"));
			}
				break;
			case Down:{
				 bytesWritten = write(uartFileDescriptor, "Down\n", sizeof("Down\n"));
			
			}
				break;
			case pressed_in:{
				 bytesWritten = write(uartFileDescriptor, "hi\n", sizeof("hi\n"));	
			}
			default:
			break;

		}

		if (bytesWritten < 0) {
			perror("An error occurred while writing to the UART device file");
		}

		sleepForMs(50); 
	}
}

// void sleepForMs(long long delayInMs){
//     const long long NS_PER_MS = 1000 * 1000; 
//     const long long NS_PER_SECOND = 1000000000;
    
//     long long delayNs = delayInMs * NS_PER_MS; 
//     int seconds = delayNs / NS_PER_SECOND;
//     int nanoseconds = delayNs % NS_PER_SECOND; 

//     struct timespec reqDelay = {seconds, nanoseconds}; 
//     nanosleep(&reqDelay, (struct timespec *) NULL);

// }
