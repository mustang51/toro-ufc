#include <Arduino.h>

#include "USBComposite.h"

// This code requires gcc on low-endian devices.

//================================================================================
//================================================================================
//	Joystick

void HIDJoystick::begin(void)
{
}

void HIDJoystick::end(void)
{
}

void HIDJoystick::setManualReportMode(bool mode)
{
	manualReport = mode;
}

bool HIDJoystick::getManualReportMode()
{
	return manualReport;
}

void HIDJoystick::safeSendReport()
{
	if (!manualReport) {
		sendReport();
	}
}

void HIDJoystick::_setButton(uint8_t button, bool val, uint8_t stack)
{
	uint32_t mask;
	uint32_t before = joyReport.buttons[stack];

	mask = ((uint32_t) 1 << ((((uint32_t) button) - 1)));
	if (val)
		joyReport.buttons[stack] |= mask;
	else
		joyReport.buttons[stack] &= ~mask;

	if (before != joyReport.buttons[stack])
		reportNeeded = true;

	safeSendReport();
}

void HIDJoystick::setButton(uint8_t button, bool val)
{
	if (button <= 32)
		_setButton(button -  0, val, 0);
	else if (button <= 64)
		_setButton(button - 32, val, 1);
	else if (button <= 96)
		_setButton(button - 64, val, 2);
}


void HIDJoystick::setAxis(uint8_t idx, uint8_t val)
{
	if (joyReport.axis[idx] != val)
		reportNeeded = true;

	joyReport.axis[idx] = val;

	safeSendReport();
}

// void HIDJoystick::setDebug(uint8_t idx, uint16_t val)
// {
// 	if (joyReport.debug[idx] != val)
// 		reportNeeded = true;

// 	joyReport.debug[idx] = val;

// 	safeSendReport();
// }
