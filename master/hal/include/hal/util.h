// Provide all the functions that are frequently used by every other files.
// Provide access to stoping whole process
// Provide real time status of the process to other threads.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#ifndef _UTIL_H_
#define _UTIL_H_

// INIT 
void Util_init(void);

// Cleanup and join thread.
void Util_cleanup(void);

// Check if the system is shut down 
bool Util_is_shutDown(void);

// Trigger shutdown event for the program
void Util_trigger_shutDown(void);

// Common Functions for easy access.
void runCommand(char* command);
void sleepForMs(long long delayInMs);
long long getTimeInMs(void);
void writeFile(char* path, char* value);
void readFile (char* path, char* value);

#endif