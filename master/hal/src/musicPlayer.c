#include "hal/musicPlayer.h"
#include <stdio.h>
#include <alsa/asoundlib.h>
#include <mpg123.h>
#include <stdbool.h> // Include this header for boolean type

#define DEFAULT_VOLUME 80
#define TOTAL_NUMBER_OF_SONGS 2
int volume;
bool musicPlaying = false; // Flag to indicate whether music is playing
int songNumber = 0;
bool isFastForward = false;
bool isFastBackwards = false;
bool isPaused = false;
static pthread_t musicPlayerThreadId;
void* musicPlayerThreadFunction(void* arg);

void musicPlayer_init(){

    musicPlayer_setVolume(DEFAULT_VOLUME);
    musicPlaying = true;
    pthread_create(&musicPlayerThreadId, NULL, musicPlayerThreadFunction, NULL);
}
int musicPlayer_getVolume(){
    return volume;
}
void musicPlayer_setVolume(int newVolume) {
    // Ensure volume is reasonable; If so, cache it for later getVolume() calls.
    if (newVolume < 0 || newVolume > 100) {
        printf("ERROR: Volume must be between 0 and 100.\n");
        return;
    }
    volume = newVolume;

    long min, max;
    snd_mixer_t *volHandle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "PCM";

    snd_mixer_open(&volHandle, 0);
    snd_mixer_attach(volHandle, card);
    snd_mixer_selem_register(volHandle, NULL, NULL);
    snd_mixer_load(volHandle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(volHandle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(volHandle);
}

// Function to play music file
void playMusicFile(const char* path) {
    snd_pcm_t* pcmHandle;
    snd_pcm_hw_params_t* params;
    int numChannels, encoding;
    unsigned int bitRate;
    unsigned char* mp3Buffer; // Stores decoded MP3 audio data
    size_t mp3BufferSize;

    // Initialize the mpg123 library
    mpg123_init();
    // Create a new mp3 handle
    mpg123_handle* mp3Handle = mpg123_new(NULL, NULL);
    // Open the MP3 file for decoding
    mpg123_open(mp3Handle, path);
    // Get the bit rate, number of channels, and encoding for the file to be played
    mpg123_getformat(mp3Handle, (long*)&bitRate, &numChannels, &encoding);
    // Allocate a buffer for the mp3 data
    mp3BufferSize = mpg123_outblock(mp3Handle);
    mp3Buffer = (unsigned char*)malloc(mp3BufferSize * sizeof(unsigned char));
    // Open the ALSA audio device for playback
    snd_pcm_open(&pcmHandle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    // Configure parameters for PCM output for the hardware
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcmHandle, params);
    snd_pcm_hw_params_set_access(pcmHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcmHandle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcmHandle, params, numChannels);
    snd_pcm_hw_params_set_rate_near(pcmHandle, params, &bitRate, 0);
    snd_pcm_hw_params(pcmHandle, params);

    // Decode the mp3 data, store in the mp3Buffer, and play it back
    size_t bytesRead = 0;
    size_t totalBytesRead = 0;
    while ((musicPlaying) && mpg123_read(mp3Handle, mp3Buffer, mp3BufferSize, &bytesRead) == MPG123_OK) {
        totalBytesRead += bytesRead;
        while(isPaused);
        if(isFastForward){
            mpg123_seek(mp3Handle, 4608, SEEK_CUR); // Seek to the specified position
            isFastForward = false;
        }
        if(isFastBackwards){
            mpg123_seek(mp3Handle, (-3)*4608, SEEK_CUR); // Seek to the specified position
            isFastBackwards = false;
        }
            snd_pcm_prepare(pcmHandle);
            snd_pcm_writei(pcmHandle, mp3Buffer, bytesRead / numChannels / sizeof(short));
    }
    // Free the mp3 buffer and close/delete handles
    free(mp3Buffer);
    snd_pcm_close(pcmHandle);
    mpg123_close(mp3Handle);
    mpg123_delete(mp3Handle);
}
void stopCurrentSong() {
    //currentPosition = 0;
    musicPlaying = false; // Set flag to stop playing current song
}
void playNextSong(){
    //musicPlaying = true; // Start playing music
    songNumber++;
    songNumber = songNumber % TOTAL_NUMBER_OF_SONGS;
    //printf("Now songNumber is %d\n", songNumber);

}
void playPreviousSong(){
    if(songNumber == 0){
        songNumber = TOTAL_NUMBER_OF_SONGS - 1;
    }
    else{
        songNumber--;
        songNumber = songNumber % TOTAL_NUMBER_OF_SONGS;
    }
}
void fastForward() {
    isFastForward = true; // Increment current position by specified seconds
}

void fastBackward(){
    isFastBackwards = true;
}

void pauseSong(){
    isPaused = true;
}

void playSong(){
    isPaused = false;
}

void* musicPlayerThreadFunction(void* arg){
    (void)arg;
    while(1) {
        switch (songNumber)
		{
		case 0:{
            musicPlaying = true;
            //printf("Playing song 0\n");
			playMusicFile("song-files/song0.mp3");
		}
			break;
		case 1:{
            musicPlaying = true;
            //printf("Playing song 1\n");
			playMusicFile("song-files/song1.mp3");
		}
			break;
		}
    }
    return NULL;
}

void musicPlayer_cleanup(){
    pthread_join(musicPlayerThreadId, NULL);
}
