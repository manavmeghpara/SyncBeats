// UDP Network that connects with the web page to control BeatBox
// A thread that responds to udp request from node js server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#ifndef _NETWORK_H_
#define _NETWORK_H_

#define MAX_LEN 1024 
#define PORT 12345 // communicate with udp server
 

// Network thread that communicates with server and reply back with data
void Network_init();

// Cleanup and join thread.
void Network_cleanup(void);

#endif
