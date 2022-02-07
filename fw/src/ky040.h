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

	Rotary(unsigned int index, unsigned int clk_pin, unsigned int data_pin,
	       unsigned int sw_pin,
	       unsigned int button_left, unsigned int button_right,
	       unsigned int button_push,
	       bool half_step = true, bool no_input_pullups = true);

	int16_t     position();
	void        poll_encoder();
	void        poll_sw();
	static void setup_all();

	static const uint8_t	POLL_ROTARY_MS = 1;
	static const uint8_t	POLL_SW_MS     = 1;
	static const uint8_t	FILTER_AMOUNT  = 20;
	static const unsigned int TIME_UP      = 50;


private:
	static const uint8_t	MAX_BUFFER     = 3;

	bool filter_sw(bool level);
        void rotary_interrupt();
        bool push(bool right);
        bool pull(bool *right);

	uint8_t index;
	uint8_t clk;
	uint8_t data;
	uint8_t sw;
 	uint8_t button_left;
 	uint8_t button_right;
	uint8_t button_push;
	bool	half_step;
	bool	no_input_pullups;

	uint8_t	 prevNextCode;
	uint16_t store;
	uint16_t events;
	uint16_t invalid_events;
	uint32_t activity_ms;
	bool     overflow;

	int      filter;

	enum RotaryState state;
	unsigned int skip;

	int16_t curpos;
	bool	movements[MAX_BUFFER];
	uint8_t movement_read;
	uint8_t movement_write;
};

void rotary_setup();

void rotary_loop();

#endif
