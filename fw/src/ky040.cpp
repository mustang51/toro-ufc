#include <Arduino.h>

#include "misc.h"
#include "ky040.h"
#include "joystick.h"

// Robust Rotary encoder reading
//
// Copyright John Main - best-microcontroller-projects.com
//

static const int8_t rot_enc_table[] = {
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
};

static Rotary *rotaries[Rotary::MAX_ROTARIES];

bool Rotary::push(bool right)
{
	if (right)
		curpos++;
	else
		curpos--;

	uint8_t count = (movement_write - movement_read) % MAX_BUFFER;

	if (count == MAX_BUFFER - 1) { // overflow
		overflow = true;
		return false;
	}

	movements[movement_write] = right;
	movement_write		  = (movement_write + 1) % MAX_BUFFER;

	return true;
}

bool Rotary::pull(bool *right)
{
	if (movement_write == movement_read) // empty
		return false;

	*right        = movements[movement_read];
	movement_read = (movement_read + 1) % MAX_BUFFER;

	return true;
}

void Rotary::rotary_interrupt()
{
	prevNextCode <<= 2;
	if (digitalRead(data)) prevNextCode |= 0x02;
	if (digitalRead(clk))  prevNextCode |= 0x01;
	prevNextCode &= 0x0f;

	events++;

	if (!rot_enc_table[prevNextCode] ) {
		invalid_events++;
		return;
	}

	store <<= 4;
	store |= prevNextCode;
	if (half_step) {
		uint8_t magic = store & 0xff;

		if      (magic == 0x2b) push(false);
		else if (magic == 0xd4) push(false);
		else if (magic == 0x17) push(true);
		else if (magic == 0xe8) push(true);
	} else {
		if      (store == 0xd42b) push(false);
		else if (store == 0xe817) push(true);
	}
}

Rotary::Rotary(unsigned int index, unsigned int clk_pin, unsigned int data_pin,
	       unsigned int sw_pin,
	       unsigned int button_left, unsigned int button_right,
	       unsigned int button_push,
	       bool half_step, bool no_input_pullups) :
	index(index), clk(clk_pin), data(data_pin),
	sw(sw_pin),
	button_left(button_left), button_right(button_right),
	button_push(button_push),
	half_step(half_step), no_input_pullups(no_input_pullups),
	prevNextCode(0), store(0), events(0), invalid_events(0),
	overflow(false), filter(0),
	state(IDLE), skip(0),
	curpos(0), movement_read(0), movement_write(0)
{
	if (no_input_pullups) {
		pinMode(clk, INPUT);
		pinMode(data, INPUT);
	} else {
		pinMode(clk, INPUT_PULLUP);
		pinMode(data, INPUT_PULLUP);
	}

	pinMode(sw, INPUT_PULLUP);

	if (digitalRead(data)) prevNextCode |= 0x02;
	if (digitalRead(clk))  prevNextCode |= 0x01;
}

int16_t Rotary::position()
{
	noInterrupts();
	int16_t pos = curpos;
	interrupts();

	return pos;
}

bool Rotary::filter_sw(bool level)
{
	if (level == HIGH) {
		if (filter < 0) {
			filter = 0;
			return false;
		}

		if (abs(filter) < FILTER_AMOUNT) {
			filter++;
			return false;
		}

		return true;

	} else {
		if (filter > 0) {
			filter = 0;
			return false;
		}

		if (abs(filter) < FILTER_AMOUNT) {
			filter--;
			return false;
		}

		return true;
	}
}

void Rotary::poll_sw()
{
	bool state = digitalRead(sw);

	if (false == filter_sw(state))
		return;

	Joystick.setButton(button_push, !state);
}

void Rotary::poll_encoder()
{
	if (state != IDLE) {
		// Button is held left or right, do we have to hold it down a bit?
		if ((millis() - activity_ms) < TIME_UP)
			return;
	}

	switch(state) {
	case IDLE:
	{
		bool activity;
		bool move_right;

		noInterrupts();
		activity = pull(&move_right);
		interrupts();

		if (!activity) {
			if (overflow) {
				overflow = false;
				Joystick.setButton(button_right, false);
				Joystick.setButton(button_left, false);
			}
			return; // no news
		}

		if (move_right) {
			state = RIGHT_PRESSED;
			if (!overflow)
				Joystick.setButton(button_right, true);
		} else {
			state = LEFT_PRESSED;
			if (!overflow)
				Joystick.setButton(button_left, true);
		}
		activity_ms = millis();
	}
	break;
	case RIGHT_PRESSED:
		if (!overflow)
			Joystick.setButton(button_right, false);
		state = IDLE;
		break;
	case LEFT_PRESSED:
		if (!overflow)
			Joystick.setButton(button_left, false);
		state = IDLE;
		break;
	}

	return;
}

#define NEWROTARY(INDEX, DATA, CLK, SW, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_PUSH, HALF, PULLUPS) { \
		rotaries[INDEX] = new Rotary(INDEX, DATA, CLK, SW, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_PUSH, HALF, PULLUPS); \
	attachInterrupt(digitalPinToInterrupt(DATA), \
			[](){rotaries[INDEX]->rotary_interrupt();}, CHANGE); \
	attachInterrupt(digitalPinToInterrupt(CLK), \
			[](){rotaries[INDEX]->rotary_interrupt();}, CHANGE); \
	}

void Rotary::setup_all()
{
	NEWROTARY(0, PA8 , PA9 , PB15, 48 , 47 , 49 , true, true);
	NEWROTARY(1, PB13, PB14, PB12, 51 , 50 , 52 , true, true);
}

void rotary_setup()
{
	Rotary::setup_all();
}

static void rotary_loop_sw(void)
{
	static unsigned long next_millis = 0;
	if (! time_expired_from(millis(), next_millis))
		return;
	next_millis += Rotary::POLL_SW_MS;

	rotaries[0]->poll_sw();
	rotaries[1]->poll_sw();

	return;
}

static void rotary_loop_enc(void)
{
	static unsigned long next_millis = 0;
	if (! time_expired_from(millis(), next_millis))
		return;
	next_millis += Rotary::POLL_ROTARY_MS;

	rotaries[0]->poll_encoder();
	rotaries[1]->poll_encoder();

	return;
}

void rotary_loop(void)
{
	rotary_loop_sw();
	rotary_loop_enc();
}
