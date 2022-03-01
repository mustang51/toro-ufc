#ifndef __KY040_H__
#define __KY040_H__

#include <Arduino.h>

enum RotaryState {
	IDLE = 0,
	RIGHT_PRESSED,
	LEFT_PRESSED,
};

class Rotary {
public:
	static const unsigned int MAX_ROTARIES = 3;

	Rotary(unsigned int index,
	       unsigned int clk_pin, unsigned int data_pin,
	       unsigned int sw_pin,
	       unsigned int button_left, unsigned int button_right,
	       unsigned int button_push,
	       bool half_step = true, bool no_input_pullups = true);

	int16_t     position();
	void        poll_encoder();
	void        poll_sw();
	void        poll_machine();
	void setup();

	static const uint8_t	POLL_ROTARY_MS = 1;
	static const uint8_t	POLL_SW_MS     = 1;
	static const uint8_t	FILTER_AMOUNT  = 3;
	static const unsigned int TIME_UP      = 50;

private:
	static const uint8_t	MAX_BUFFER     = 3;

	bool filter_sw_fn(bool level);
        bool push(bool right);
        bool pull(bool *right);

	uint8_t index;
	uint8_t clk_pin;
	uint8_t data_pin;
	uint8_t sw_pin;
	char clk;
	char data;

 	uint8_t button_left;
 	uint8_t button_right;
	uint8_t button_push;
	bool	half_step;
	bool	no_input_pullups;

	uint16_t events;
	uint32_t activity_ms;
	bool     overflow;

	enum RotaryState state;

	int16_t curpos;
	int8_t  filter_data;
	int8_t  filter_clk;
	int8_t  filter_sw;
	bool	movements[MAX_BUFFER];
	uint8_t movement_read;
	uint8_t movement_write;
};

void rotary_setup();

void rotary_loop();

#endif
