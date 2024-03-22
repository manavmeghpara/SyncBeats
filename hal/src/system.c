#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hal/system.h"

#define MAX_OUTPUT_SIZE 1024
#define MS_PER_S 1000
#define US_PER_S 1000000
#define NS_PER_S 1000000000
#define NS_PER_MS 1000000
#define NS_PER_US 1000

void system_exec(char* command)
{
    // Execute command in subprocess (output into pipe)
    FILE* pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[MAX_OUTPUT_SIZE];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL) {
            break;
        }
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void system_sleepForMs(long long sleepTimeMs)
{
    long long sleepTimeNS = sleepTimeMs * NS_PER_MS;
    int s = sleepTimeNS / NS_PER_S;
    int ns = sleepTimeNS % NS_PER_S;

    struct timespec sleepTimeSpec = { s, ns };
    nanosleep(&sleepTimeSpec, NULL);
}

long long system_getTimeMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    long long s = spec.tv_sec;
    long long ns = spec.tv_nsec;
    long long totalMs = s * MS_PER_S + ns / NS_PER_MS;

    return totalMs;
}

long long system_getTimeUs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    long long s = spec.tv_sec;
    long long ns = spec.tv_nsec;
    long long totalUs = s * US_PER_S + ns / NS_PER_US;

    return totalUs;
}
