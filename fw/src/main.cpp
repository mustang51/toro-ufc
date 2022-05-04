#include <Arduino.h>
#include "ky040.h"
#include "heartbeat.h"
#include "joystick.h"
#include "analog.h"
#include "key_matrix.h"

void setup()
{
	disableDebugPorts();

	heartbeat_setup();
	joystick_setup();
	rotary_setup();
	analog_setup();
	keymatrix_setup();
}

void loop()
{
	heartbeat_loop();
	analog_loop();
	rotary_loop();
	keymatrix_loop();
	joystick_report();  // horribly slow and blocking :(
}


