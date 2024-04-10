#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <pthread.h> 
#include <unistd.h>
#include <stdio.h> 
#include <time.h> 

#include "uart.h"
#include "util.h"
#include "musicPlayer.h"

enum commands{
    PLAY, 
    STOP, 
    VOLUME_UP,
    VOLUME_DOWN,
    NEXT,
    PREVIOUS,
    SPEECH
};
void bluetooth_init(); 
void bluetooth_cleanup(); 
void* readDataFromBle(void* fd);
#endif