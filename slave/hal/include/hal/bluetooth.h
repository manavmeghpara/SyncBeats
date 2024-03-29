#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <pthread.h> 
#include <unistd.h>
#include <stdio.h> 
#include <time.h> 

enum commands{Play, Stop, Vol_UP, Vol_DOWN};
void bluetooth_init(); 
void bluetooth_cleanup(); 
void* readDataFromBle(void* fd);
void sleepForMs(long long delayInMs);
#endif