// -*- mode: c++; c-file-style: "linux" -*-

#include <Arduino.h>
#include <libmaple/iwdg.h>

#include "heartbeat.h"
#include "misc.h"

// #define WATCHDOG

#define BEAT_WAITING_MILLIS   700
#define BEAT_SISTOLIC_MILLIS  100
#define BEAT_PAUSE_MILLIS     100
#define BEAT_DIASTOLIC_MILLIS 100

enum {
	BEAT_WAITING = 0,
	BEAT_SISTOLIC,
	BEAT_PAUSE,
	BEAT_DIASTOLIC
};

#define LED_PIN PC13

void heartbeat_loop(void)
{
	static unsigned char beating_stage = BEAT_WAITING;
	static unsigned long next_millis = 0;

#ifdef WATCHDOG
	iwdg_feed(); // have the wdt reset the chip
#endif
	if (! time_expired_from(millis(), next_millis))
		return;

	/* cycle the state-machine */
	switch (beating_stage) {
	case BEAT_WAITING:
		digitalWrite(LED_PIN, HIGH);

		next_millis = next_millis + BEAT_SISTOLIC_MILLIS;

		beating_stage = BEAT_SISTOLIC;
		break;
	case BEAT_SISTOLIC:
		digitalWrite(LED_PIN, LOW);

		next_millis = next_millis + BEAT_PAUSE_MILLIS;

		beating_stage = BEAT_PAUSE;

		break;
	case BEAT_PAUSE:
		digitalWrite(LED_PIN, HIGH);

		next_millis = next_millis + BEAT_DIASTOLIC_MILLIS;

		beating_stage = BEAT_DIASTOLIC;
		break;
	case BEAT_DIASTOLIC:
		digitalWrite(LED_PIN, LOW);

		next_millis = next_millis + BEAT_WAITING_MILLIS;

		beating_stage = BEAT_WAITING;
		break;
	}

	return;
}

void heartbeat_setup(void)
{
	pinMode(LED_PIN, OUTPUT);

#ifdef WATCHDOG
	// 40 KHz clock, prescaled 32, count up to 2500, that is 2 sec.
	iwdg_init(IWDG_PRE_32, 2500); // have the wdt reset the chip
#endif
}
