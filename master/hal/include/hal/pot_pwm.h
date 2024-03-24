#ifndef POT_PWM_H
#define POT_PWM_H

#include <pthread.h>


// Function to initialize the potentiometer and PWM LED control
void pot_pwm_init();

// Function to read potentiometer value and update PWM frequency for LED control
void update_pwm_frequency();

// Thread function to continuously update PWM frequency
void *pwm_thread_function(void* args);

void pot_pwm_cleanup();

int get_pot_value();

#endif
