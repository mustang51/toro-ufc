#include <Arduino.h>

#include "analog.h"
#include "misc.h"
#include "joystick.h"

static const unsigned int ANALOG_POLL_MS = 20;
static const float EMA_ALPHA = 0.3;
static const uint8_t channels[] = {7, 6};
static const unsigned int analogs = sizeof(channels);
static const uint8_t buttons[][2] = {
	{53, 54},
	{55, 56},
};

static float EMA_LP[] = {0, 0};
static unsigned int values[] = {300, 300};

void ema_low_pass_filter(unsigned int index, float new_value)
{
	EMA_LP[index] = EMA_ALPHA * new_value + (1.0 - EMA_ALPHA) * EMA_LP[index];
}

bool low_pass(unsigned int index)
{
	unsigned int current = values[index] * 16;
	unsigned int ema = round(EMA_LP[index]);

	if (abs(ema - current) < 32)
		return false;

	values[index] = ema / 16;

	return true;
}

void analog_loop(void)
{
	static unsigned long next_millis = 0;
	if (! time_expired_from(millis(), next_millis))
		return;
	next_millis += ANALOG_POLL_MS;

	for (unsigned int a = 0; a < analogs; a++) {
		ema_low_pass_filter(a, analogRead(channels[a]));
		if (low_pass(a)) {
			Joystick.setAxis(a, values[a]);
			if (values[a] <= 5) {
				Joystick.setButton(buttons[a][1], false);
				Joystick.setButton(buttons[a][0], true);
			} else if (values[a] >= 250) {
				Joystick.setButton(buttons[a][0], false);
				Joystick.setButton(buttons[a][1], true);
			} else {
				Joystick.setButton(buttons[a][0], false);
				Joystick.setButton(buttons[a][1], false);
			}
		}
	}

	return;
}

void analog_setup(void)
{

}
