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

void HIDJoystick::setButton(uint8_t button, bool val)
{
	uint64_t mask;
	uint64_t before = joyReport.buttons;

	mask = ((uint64_t) 1 << ((button - 1)));
	if (val)
		joyReport.buttons |= mask;
	else
		joyReport.buttons &= ~mask;

	if (before != joyReport.buttons)
		reportNeeded = true;

	safeSendReport();
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
