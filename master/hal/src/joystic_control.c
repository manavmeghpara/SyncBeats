#include "hal/joystick_control.h"
#include "hal/musicPlayer.h"
#include "hal/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

pthread_t joysticID;

void* joystickThreadFunction(void* args);

void joystick_init(){
	pthread_create(&joysticID, NULL, joystickThreadFunction, NULL);
}
void joystick_cleanup(){
	pthread_join(joysticID, NULL);
}

int readFromFileToScreen(char *fileName) {
	FILE *file = fopen( fileName, "r");
	if (file == NULL) {
		printf( "ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}
	char buff[1024];
	fgets(buff, 1024, file);
	fclose(file);
	return atoi(buff);
}

enum eJoystickDirections getDirections() {
	if (readFromFileToScreen("/sys/class/gpio/gpio65/value") == 0) {
		return Left;
	} else if(readFromFileToScreen("/sys/class/gpio/gpio47/value") == 0){	
		return Right;
	} else if(readFromFileToScreen("/sys/class/gpio/gpio26/value") == 0){
		return Up;
	} else if (readFromFileToScreen("/sys/class/gpio/gpio46/value") == 0){
		return Down;
	} else if(readFromFileToScreen("/sys/class/gpio/gpio27/value") == 0)
        return pressed_in;
         else {
		return no_direction;
	}
}

void* joystickThreadFunction(void* args){
	(void)args;
	musicPlayer_setVolume(80);
	bool isPaused = false;
	while (1){
		
		enum eJoystickDirections direction;
		direction = getDirections();
		switch (direction)
		{
		case Left:{
			stopCurrentSong();
			playPreviousSong();
			sleepForMs(300);
		}
			break;
		case Right:{
			//printf("Stopping current song\n");
			stopCurrentSong();
			playNextSong();
			sleepForMs(300);
		}
			break;
		case Up:{
			fastForward();
			sleepForMs(100);
		}
			break;
		case Down:{
			fastBackward();
			sleepForMs(100);
		}
			break;
		case pressed_in:{
			if(isPaused){
				playSong();
				isPaused = false;
			}
			else{
				pauseSong();
				isPaused = true;
			}
			
			sleepForMs(300);
		}
		default:
			break;
		}
	}
	return NULL;
}