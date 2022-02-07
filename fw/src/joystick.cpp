#include <Arduino.h>
#include <USBComposite.h>

#include "joystick.h"
#include "misc.h"

USBHID HID;
HIDJoystick Joystick(HID);

void joystick_report()
{
	Joystick.send();
}

void joystick_setup()
{
	HID.begin(HID_JOYSTICK);

	Joystick.setManualReportMode(true);
}
