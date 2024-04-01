#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <pthread.h>

// Function to initialize the music player
void musicPlayer_init();

// Function to cleanup the music player
void musicPlayer_cleanup();

// Function to set PCM volume using ALSA mixer
void musicPlayer_setVolume(int newVolume);

int musicPlayer_getVolume();

void stopCurrentSong();

void playNextSong();

void playPreviousSong();

void fastForward();

void fastBackward();

void pauseSong();

void playSong();

// Function to play music in a separate thread
void* musicPlayer_playMusic(void* arg);

#endif