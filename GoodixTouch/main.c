/*
 * main.c
 *
 * Created: 8/13/2020 09:39:35
 * Author : azuko
 */ 

#include "libs/goodix/goodix.h"
#include "libs/goodix/calibrator.h"
#include "libs/usb/usb.h"
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>


volatile uint8_t touchContacts = 0;
volatile GTPoint *touchPoints;

void handleTouch(int8_t contacts, GTPoint *points) {
	if(!Calibrator_adjust(contacts, points)) {
		return; // calibration in progress
	}
	
	touchContacts = contacts;
	touchPoints = points;
}

bool createHIDReport(USB_DigitizerReport_Data_t* report) {
	GTPoint *points = touchPoints;
	uint8_t contacts = touchContacts;
	
	report->Finger0_ContactIdentifier = 0;
	report->Finger0_InRange = 1;
	if(contacts > 0) {
		report->Finger0_TipSwitch = 1;
		report->Finger0_X = points[0].x;
		report->Finger0_Y = points[0].y;
	}
  
	report->Finger1_ContactIdentifier = 1;
	report->Finger1_InRange = 1;
	if(contacts > 1) {
		report->Finger1_TipSwitch = 1;
		report->Finger1_X = points[1].x;
		report->Finger1_Y = points[1].y;
	}

	report->Finger2_ContactIdentifier = 2;
	report->Finger2_InRange = 1;
	if(contacts > 2) {
		report->Finger2_TipSwitch = 1;
		report->Finger2_X = points[2].x;
		report->Finger2_Y = points[2].y;
	}

	report->Finger3_ContactIdentifier = 3;
	report->Finger3_InRange = 1;
	if(contacts > 3) {
		report->Finger3_TipSwitch = 1;
		report->Finger3_X = points[3].x;
		report->Finger3_Y = points[3].y;
	}

	report->Finger4_ContactIdentifier = 4;
	report->Finger4_InRange = 1;
	if(contacts > 4) {
		report->Finger4_TipSwitch = 1;
		report->Finger4_X = points[4].x;
		report->Finger4_Y = points[4].y;
	}

	report->ContactCount = contacts;
	return contacts > 0;
}

void init() {
	// Disable watchdog if enabled by bootloader/fuses 
	MCUSR &= ~(1 << WDRF);
	wdt_disable();
	
	// Disable clock division
	clock_prescale_set(clock_div_1);

	// Goodix init
	Goodix_setHandler(handleTouch);
	Goodix_begin(); // error when status == 0
	// Goodix_test(); // error when error > 0
	
	// Calibrator init
	Calibrator_init();
	
	// USB init
	USB_setHIDCreateHandler(createHIDReport);
	USB_init();
	
	// Timer 0
	TCCR0A = 0;
	TCCR0B = CS02 | CS01; // CK/1024
	TIMSK0 = (1 << OCIE0A); // Output Compare Match A Interrupt Enable
	OCR0A = 128; // ~10ms
		
	sei();
}

int main(void) {
	
	init();
	
    while(1) {	
		Goodix_loop(); // handle goodix input

		_delay_ms(1);		
		
		USB_loop(); // handle usb routine
    }
}


ISR(TIMER0_COMPA_vect) {
	Calibrator_tic();
}
