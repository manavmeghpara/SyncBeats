#include "hal/util.h"

bool is_shutDown;

void Util_init(void)
{
    is_shutDown = false;
}
void Util_cleanup(void)
{
    
}

bool Util_is_shutDown(){
    return is_shutDown;
}

void Util_trigger_shutDown(void)
{
    is_shutDown = true;
}

void runCommand(char* command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        //printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode =  WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

long long getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000
    + nanoSeconds / 1000000;
    return milliSeconds;
}



void writeFile(char* path, char* value)
{

    FILE * f = fopen(path, "w");

    if (f == NULL) {
        printf("ERROR OPENING %s.", path);
		return;
    }

    int charWritten = fprintf(f, value);
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return;
    }
    
    fclose(f);

}

void readFile(char* path, char* value)
{

    FILE * f = fopen(path, "r");

    if (f == NULL) {
        printf("ERROR OPENING %s.", path);
		return;
    }

    fgets(value, 1024, f);
    
    fclose(f);

}