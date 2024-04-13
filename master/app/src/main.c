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
    Util_init();
    bluetooth_init(); 
    musicPlayer_init();
    joystick_init();
    pot_pwm_init();
    //Network_init();
    while(!Util_is_shutDown());
    //Network_cleanup();
    pot_pwm_cleanup();
    joystick_cleanup();
    musicPlayer_cleanup();
    bluetooth_cleanup(); 
    Util_cleanup();

    return 0;
}      
 