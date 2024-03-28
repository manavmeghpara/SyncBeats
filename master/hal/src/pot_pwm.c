#include "hal/pot_pwm.h"
#include "hal/util.h"
#include "hal/musicPlayer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define A2D_FILE_VOLTAGE0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define PWM_PERIOD_FILE "/dev/bone/pwm/0/b/period"
#define PWM_DUTY_CYCLE_FILE "/dev/bone/pwm/0/b/duty_cycle"
#define PWM_CONFIG_PIN_COMMAND "config-pin p9_21 pwm"
#define PWM_ENABLE_FILE "/dev/bone/pwm/0/b/enable"



// 10000000 duty_cycle
int last_value = -1;
pthread_t pwm_thread;
int pot_value = 0;

// Function to read the potentiometer value
int read_pot_value()
{
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE0, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }

    // Get reading
    int a2dReading = 0;
    int itemsRead = fscanf(f, "%d", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }

    // Close file
    fclose(f);
    return a2dReading;
}

void configure_pwm_pin() {
    // Execute the config-pin command to configure p9_21 for PWM
    runCommand(PWM_CONFIG_PIN_COMMAND);
}

// Function to initialize the potentiometer and PWM LED control
void pot_pwm_init() {
    configure_pwm_pin(); // Configure p9_21 for PWM
    pthread_create(&pwm_thread, NULL, pwm_thread_function, NULL);
}

void set_duty_cycle(){
    writeFile(PWM_DUTY_CYCLE_FILE, "10000000");
}

// Function to set the PWM frequency based on potentiometer value
void set_pwm_frequency(int pot_value) {
    // Compute period
    double period = (double)(1000000000)/(pot_value / 40);
    //printf("period value = %f\n", period);

    char result[50];
    snprintf(result, 50, "%d", (int)period);  
    writeFile(PWM_PERIOD_FILE, result);

}

// Function to read potentiometer value and update PWM frequency for LED control
void update_pwm_frequency() {
    pot_value = read_pot_value();
    if((last_value != pot_value)){
        set_pwm_frequency(pot_value);
        last_value = pot_value;
    }

    //sleepForMs(100);
}

// Thread function to continuously update PWM frequency
void *pwm_thread_function(void* args) {
    (void)args;

    while (1) {
        set_duty_cycle();
        update_pwm_frequency();
        // Sleep or delay
        //read_pot_value();
        //printf("POT value = %d\n", pot_value);
        //printf("Volume = %d\n", pot_value/41);
        musicPlayer_setVolume(pot_value/41);
        sleepForMs(100);
    }
    return NULL;
}

int get_pot_value(){
    return pot_value;
}

void pot_pwm_cleanup(){
    pthread_join(pwm_thread, NULL);
}
