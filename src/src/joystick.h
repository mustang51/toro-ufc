#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <USBComposite.h>

extern HIDJoystick Joystick;

void joystick_setup();

void joystick_report();

#endif
