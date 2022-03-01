#include <Arduino.h>

#include "misc.h"
#include "ky040.h"
#include "joystick.h"

static Rotary rotary0(0, PB13, PB12, PC15, 63 , 64 , 65 , true, true);
static Rotary rotary1(1, PB15, PB14, PC14, 66 , 67 , 68 , true, true);

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

Rotary::Rotary(unsigned int index,
	       unsigned int clk, unsigned int data,
	       unsigned int sw,
	       unsigned int button_left, unsigned int button_right,
	       unsigned int button_push,
	       bool half_step, bool no_input_pullups) :
	index(index), clk_pin(clk), data_pin(data),
	sw_pin(sw),
	button_left(button_left), button_right(button_right),
	button_push(button_push),
	half_step(half_step), no_input_pullups(no_input_pullups),
	events(0), overflow(false),
	state(IDLE),
	curpos(0),
	filter_data(0), filter_clk(0), filter_sw(0),
	movement_read(0), movement_write(0)
{
}

void Rotary::setup()
{
	if (no_input_pullups) {
		pinMode(clk_pin, INPUT);
		pinMode(data_pin, INPUT);
	} else {
		pinMode(clk_pin, INPUT_PULLUP);
		pinMode(data_pin, INPUT_PULLUP);
	}

	pinMode(sw_pin, INPUT_PULLUP);

	data = (digitalRead(data_pin) == 1) ? FILTER_AMOUNT : -FILTER_AMOUNT;
	clk = (digitalRead(clk_pin) == 1) ? FILTER_AMOUNT : -FILTER_AMOUNT;
}

bool Rotary::filter_sw_fn(bool level)
{
	if (level == HIGH) {
		if (filter_sw < 0) {
			filter_sw = 0;
			return false;
		}
		if (abs(filter_sw) < FILTER_AMOUNT) {
			filter_sw++;
			return false;
		}
	} else {
		if (filter_sw > 0) {
			filter_sw = 0;
			return false;
		}
		if (abs(filter_sw) < FILTER_AMOUNT) {
			filter_sw--;
			return false;
		}
	}
	return true;
}

void Rotary::poll_sw()
{
	bool state = digitalRead(sw_pin);

	if (false == filter_sw_fn(state))
		return;

	Joystick.setButton(button_push, !state);
}

void Rotary::poll_encoder()
{
	char new_data = digitalRead(data_pin);
	char new_clk = digitalRead(clk_pin);

	if ((new_data == 1) && (filter_data < FILTER_AMOUNT))
		filter_data++;
	if ((new_data == 0) && (-filter_data < FILTER_AMOUNT))
		filter_data--;

	if ((new_clk == 1) && (filter_clk < FILTER_AMOUNT))
		filter_clk++;
	if ((new_clk == 0) && (-filter_clk < FILTER_AMOUNT))
		filter_clk--;

	if ((filter_data != FILTER_AMOUNT) && (filter_data != -FILTER_AMOUNT))
		new_data = data;
	else
		new_data = filter_data;

	if ((filter_clk != FILTER_AMOUNT) && (filter_clk != -FILTER_AMOUNT))
		new_clk = clk;
	else
		new_clk = filter_clk;

	if ((new_data == data) && (new_clk == clk))
		return;

	if (half_step) {
		if (new_data != new_clk) {
			events++;
			if (new_data != data)
				push(false);
			else
				push(true);
		}
	}

	data = new_data;
	clk  = new_clk;
}

void Rotary::poll_machine()
{
	unsigned long now = millis();
	if (state != IDLE) {
		// Button is held left or right, do we have to hold it down a bit?
		if ((now - activity_ms) < TIME_UP)
			return;
	}

	switch(state) {
	case IDLE:
	{
		bool activity;
		bool move_right;

		activity = pull(&move_right);

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
		activity_ms = now;
	}
	break;
	case RIGHT_PRESSED:
		if (!overflow) {
			Joystick.setButton(button_right, false);
		}
		state = IDLE;
		break;
	case LEFT_PRESSED:
		if (!overflow) {
			Joystick.setButton(button_left, false);
		}
		state = IDLE;
		break;
	}

	return;
}

static void rotary_loop_sw(void)
{
	static unsigned long next_millis = 0;
	if (! time_expired_from(millis(), next_millis))
		return;
	next_millis += Rotary::POLL_SW_MS;

	rotary0.poll_sw();
	rotary1.poll_sw();

	return;
}

static void rotary_loop_enc(void)
{
	static unsigned long next_millis = 0;
	if (! time_expired_from(millis(), next_millis))
		return;
	next_millis += Rotary::POLL_ROTARY_MS;

	rotary0.poll_encoder();
	rotary0.poll_machine();

	rotary1.poll_encoder();
	rotary1.poll_machine();

	return;
}

void rotary_setup()
{
	rotary0.setup();
	rotary1.setup();
}

void rotary_loop(void)
{
	rotary_loop_sw();
	rotary_loop_enc();
}
