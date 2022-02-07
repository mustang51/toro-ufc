#include "key_matrix.h"
#include "misc.h"
#include "joystick.h"

#include <Arduino.h>

const unsigned int SCAN_MATRIX_MICROS = 100;
const unsigned int FILTER_AMOUNT = 20;

static uint8_t column_pins[] = {
	PB1, PB10, PB11, PB9, PB8, PB7
};

static uint8_t columns = sizeof(column_pins);

static uint8_t row_pins[] = {
	PB0, PA5, PA4, PA3, PA2, PA1, PA0
};

static uint8_t rows = sizeof(row_pins);

static uint8_t key_press[sizeof(column_pins)][sizeof(row_pins)] =
{
	{26,  1,  2,  3, 13, 14,  6},
	{ 7, 38, 31, 29, 28,  4,  5},
	{46, 11, 10, 12,  8,  9, 15},
	{44, 34, 40, 43, 37, 17, 16},
 	{32, 41, 42, 39, 35, 18,  0},
	{19, 20, 21, 22, 23, 24, 25},
};

static uint8_t key_release[sizeof(column_pins)][sizeof(row_pins)] =
{
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
};

static uint8_t key_triple[][3] =
{
 	{26, 28, 27},
 	{29, 31, 30},
 	{32, 34, 33},
 	{35, 37, 36},
 	{44, 46, 45},
};

static uint8_t key_fifth[][5] =
{
 	{40, 41, 42, 43, 57},
};

static bool scan_change = false;

static uint8_t triples = sizeof(key_triple) / 3;
static uint8_t fifths = sizeof(key_fifth) / 5;

static bool scan_state[sizeof(column_pins)][sizeof(row_pins)];

static int filter_state[sizeof(column_pins)][sizeof(row_pins)];

static uint8_t scan_row = 0;

bool is_pressed(uint8_t button)
{
	for (uint8_t r = 0; r < columns; r++) {
		for (uint8_t c = 0; c < rows; c++) {
			if (key_press[r][c] != button)
				continue;
			return !scan_state[r][c];
		}
	}
	return false;
}

bool all_triples_off(uint8_t index)
{
	bool ret = true;
	for (unsigned int t = 0; t < 2; t++)
		ret &= !is_pressed(key_triple[index][t]);
	return ret;
}

bool all_fifths_off(uint8_t index)
{
	bool ret = true;
	for (unsigned int t = 0; t < 4; t++)
		ret &= !is_pressed(key_fifth[index][t]);
	return ret;
}

bool filter_position(bool level, uint8_t r, uint8_t c)
{
	if (level == HIGH) {
		if (filter_state[r][c] < 0) {
			filter_state[r][c] = 0;
			return false;
		}

		if (abs(filter_state[r][c]) < FILTER_AMOUNT) {
			filter_state[r][c]++;
			return false;
		}

		return true;

	} else {
		if (filter_state[r][c] > 0) {
			filter_state[r][c] = 0;
			return false;
		}

		if (abs(filter_state[r][c]) < FILTER_AMOUNT) {
			filter_state[r][c]--;
			return false;
		}

		return true;
	}
}

static void scan_position(uint8_t scan_column)
{
	// scan the current column
	bool level = digitalRead(column_pins[scan_column]);

	if (false == filter_position(level, scan_column, scan_row))
		return;

	scan_state[scan_column][scan_row] = level;

	if (LOW == level) { // key pressed
		if (key_release[scan_column][scan_row] != 0) {
			Joystick.setButton(key_release[scan_column][scan_row], false);
			scan_change = true;
		}

		if (key_press[scan_column][scan_row] != 0) {
			Joystick.setButton(key_press[scan_column][scan_row], true);
			scan_change = true;
		}
	} else { // key released
		if (key_press[scan_column][scan_row] != 0) {
			Joystick.setButton(key_press[scan_column][scan_row], false);
			scan_change = true;
		}

		if (key_release[scan_column][scan_row] != 0) {
			Joystick.setButton(key_release[scan_column][scan_row], true);
			scan_change = true;
		}
	}

	return;
}

void scan_triples(void)
{
	if (!scan_change)
		return;

	for (uint8_t t = 0; t < triples; t++) {
		if (all_triples_off(t))
			Joystick.setButton(key_triple[t][2], true);
		else
			Joystick.setButton(key_triple[t][2], false);
	}
}

void scan_fifths(void)
{
	if (!scan_change)
		return;

	for (uint8_t f = 0; f < fifths; f++) {
		if (all_fifths_off(f))
			Joystick.setButton(key_fifth[f][4], true);
		else
			Joystick.setButton(key_fifth[f][4], false);
	}
}

void keymatrix_loop(void)
{
	static unsigned long next_micros = 0;

	if (! time_expired_from(micros(), next_micros))
		return;

	next_micros += SCAN_MATRIX_MICROS;

	for (uint8_t scan_column = 0; scan_column < columns; scan_column++)
		scan_position(scan_column);

	// starting new row, turn off the current one
	digitalWrite(row_pins[scan_row], HIGH);

	scan_row++;
	if (scan_row >= rows) {
                // full matrix scanned.
		scan_row = 0;
		scan_triples();
		scan_fifths();
		scan_change = false;
	}

	// enable the next one and wait for next scan to stabilize
	pinMode(row_pins[scan_row], OUTPUT);
	digitalWrite(row_pins[scan_row], LOW);

	return;
}

void keymatrix_setup()
{
	for (unsigned int r = 0; r < columns; r++) {
		for (unsigned int c = 0; c < rows; c++) {
			filter_state[r][c] = 0;
			scan_state[r][c] = true;
		}
	}

	for (unsigned int r = 0; r < columns; r++)
		pinMode(column_pins[r], INPUT_PULLUP);

	for (unsigned int c = 0; c < rows; c++) {
		pinMode(row_pins[c], OUTPUT);
		digitalWrite(row_pins[c], HIGH);
	}

	// prepare the first row to be scanned
	pinMode(row_pins[0], OUTPUT);
	digitalWrite(row_pins[0], LOW);
}
