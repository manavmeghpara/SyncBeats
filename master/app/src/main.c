#include "hal/uart.h"
#include "hal/musicPlayer.h"
#include "hal/joystick_control.h"
#include "hal/network.h"
#include "hal/pot_pwm.h"
#include "hal/bluetooth.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024
// file for reading and writing to
#define UART_DEVICE "/dev/ttyS4"



int main()
{
    bluetooth_init(); 
    musicPlayer_init();
    joystick_init();
    pot_pwm_init();
    Network_init();
    while(1);
    Network_cleanup();
    pot_pwm_cleanup();
    joystick_cleanup();
    musicPlayer_cleanup();
    bluetooth_cleanup(); 

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
