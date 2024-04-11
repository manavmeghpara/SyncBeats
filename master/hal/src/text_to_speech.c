#include "hal/text_to_speech.h"
#include "hal/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <lame/lame.h>


lame_t lame;
char path[256];

typedef struct _Thread_Data_t {
    char *fileName;
    char *folderName;
} Thread_Data_t;

#define WAV_SIZE 8192
#define MP3_SIZE 8192

void lameEncoderInit(void) {
    lame = lame_init();
    lame_set_in_samplerate(lame, 11025);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);
}

void lameEncoderClose(void) {
    lame_close(lame);
}

char *renameFile(const char *fName) {
    char *fLocal, *rmDot, *fNewExt = ".mp3";

    if (fName == NULL)
        return NULL;
    if ((fLocal = malloc(strlen(fName) + 1)) == NULL)
        return NULL;
    strcpy(fLocal, fName);
    rmDot = strrchr(fLocal, '.');
    if (rmDot != NULL)
        *rmDot = '\0';
    strcat(fLocal, fNewExt);
    return fLocal;
}

void *mp3FromWav(void *arg) {
    Thread_Data_t *inData = (Thread_Data_t *)arg;
    char *fileName = inData->fileName;
    char *address = inData->folderName;
    int read, write;

    char absFilePath[255];
    strcpy(absFilePath, address);
    strcat(absFilePath, "/");
    strcat(absFilePath, fileName);

    FILE *wavFile = fopen(absFilePath, "rb");
    if (!wavFile) {
        printf("%s is not found!\n", absFilePath);
        pthread_exit(NULL);
        return NULL;
    }

    char *newFileName = renameFile(fileName);
    char absNewFilePath[255];
    strcpy(absNewFilePath, address);
    strcat(absNewFilePath, "/");
    strcat(absNewFilePath, newFileName);
    free(newFileName);

    FILE *mp3File = fopen(absNewFilePath, "wb");
    if (!mp3File) {
        printf("Failed to create output file: %s\n", absNewFilePath);
        fclose(wavFile);
        pthread_exit(NULL);
        return NULL;
    }

    short int wavBuffer[WAV_SIZE * 2];
    unsigned char mp3Buffer[MP3_SIZE];

    lameEncoderInit();

    do {
        read = fread(wavBuffer, 2 * sizeof(short int), WAV_SIZE, wavFile);
        if (read == 0) {
            write = lame_encode_flush(lame, mp3Buffer, MP3_SIZE);
        } else {
            write = lame_encode_buffer_interleaved(lame, wavBuffer, read, mp3Buffer, MP3_SIZE);
        }
        fwrite(mp3Buffer, write, 1, mp3File);
    } while (read != 0);

    lameEncoderClose();

    fclose(mp3File);
    fclose(wavFile);

    pthread_exit(NULL);
    return NULL;
}

char* text_to_speech(char* text){
    char command[256];
    snprintf(command, sizeof(command), "espeak '%s' -w song-files/test.wav", text);
    runCommand(command);
    snprintf(path, sizeof(path), "song-files/test.wav");
	convertWavToMp3(path);
    snprintf(path, sizeof(path), "song-files/test.mp3");
    return path;
}

void convertWavToMp3(const char *wavFilePath) {
    char *folderAddr = NULL;
    char *fileName = NULL;

    // Split the path into folder address and file name
    const char *lastSlash = strrchr(wavFilePath, '/');
    if (lastSlash != NULL) {
        folderAddr = malloc((lastSlash - wavFilePath + 2) * sizeof(char));
        strncpy(folderAddr, wavFilePath, lastSlash - wavFilePath + 1);
        folderAddr[lastSlash - wavFilePath + 1] = '\0';
        fileName = strdup(lastSlash + 1);
    } else {
        folderAddr = strdup("");
        fileName = strdup(wavFilePath);
    }

    // Create thread data structure
    Thread_Data_t threadData;
    threadData.fileName = fileName;
    threadData.folderName = folderAddr;

    // Start the thread
    pthread_t thread;
    pthread_create(&thread, NULL, mp3FromWav, &threadData);

    // Wait for the thread to finish
    pthread_join(thread, NULL);
    printf("mp3 file changed\n");
    // Free allocated memory
    free(fileName);
    free(folderAddr);
}