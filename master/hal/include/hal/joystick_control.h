// JOYSTICK access to control beaglebone music player

#ifndef JOYSTICK_CONTROL_H
#define JOYSTICK_CONTROL_H

// Joystick up - volume up +5
// Joystick down - volume down -5
// Joystick left - tempo low -5
// Joystick right - tempo high +5
// Joystick push - change playlist
enum eJoystickDirections { Left, Right, Up, Down, pressed_in, no_direction};

// creates thread that reads input continuously
void joystick_init();

// Cleanup and join thread.
void joystick_cleanup();

// Returns the reading from file
// 1 = off
// 0 = on (button presses)
int readFromFileToScreen(char *fileName);

// returns the enum corresponding to any dir
enum eJoystickDirections getDirections();


#endif