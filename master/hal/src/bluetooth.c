#include "hal/bluetooth.h"
#include "hal/joystick_control.h"
#include "hal/util.h"

#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS4"
static pthread_t writeTid;
static int fd; 

void bluetooth_init(){
	fd = uart_init(UART_DEVICE);
	pthread_create(&writeTid, NULL, readDataFromBle, (void*)&fd);
}


void bluetooth_cleanup(){
	pthread_cancel(writeTid); 
	pthread_join(writeTid, NULL);
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
                case PLAY:{
                    printf("Play\n");
					playSong();
                }
                break; 
                case STOP:{
                    printf("Stop\n");	
					pauseSong();
                }
                    break;
                case VOLUME_UP:{
                    printf("V Up\n");
					int v = musicPlayer_getVolume();
					musicPlayer_setVolume(v+10);
                }
                    break;
                case VOLUME_DOWN:{
                    printf("V Down\n");
					int v = musicPlayer_getVolume();
					musicPlayer_setVolume(v-10);
                
                }
				break;
				case NEXT:{
                    printf("Next\n");	
                    stopCurrentSong();
					playNextSong();
                }
                    break;
				case PREVIOUS:{
                    printf("Previous\n");
                    stopCurrentSong();	
					playPreviousSong();
                }
                    break;
                case SPEECH:{
                    printf("Text to speech\n");
                    while(1){
                        // uart_read(uartFileDescriptor, rx_buffer);
                        int bytesRead = read(uartFileDescriptor, &rx_buffer, 1);
                        if (bytesRead < 0) {
                            perror("Error occurred while reading UART device file");
                        }else{
                            printf("%c", rx_buffer);
                        }
                    }
                }
                break;
                default:
                break;

                }
            }
            
        }
        sleepForMs(50); 
    }
}
