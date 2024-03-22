#ifndef SYSTEM_H
#define SYSTEM_H

// Executes terminal command (read-only)
void system_exec(char* command);

// Sleep
void system_sleepForMs(long long sleepTimeMs);

// Get current time
long long system_getTimeMs(void);
long long system_getTimeUs(void);

#endif // SYSTEM_H
