#include "hal/uart.h"
#include "hal/bluetooth.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    bluetooth_init(); 
    while(1);
    bluetooth_cleanup(); 

    return 0;
}