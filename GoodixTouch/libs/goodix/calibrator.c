/*
 * calibrator.c
 *
 * Created: 8/14/2020 12:12:17
 *  Author: azuko
 */ 
#include <stdint.h>

#include "../../io.h"
#include "goodix.h"
#include <avr/eeprom.h>

#define LOGICAL_MAX_X 2047.0F
#define LOGICAL_MAX_Y 2047.0F

#define STAGE_IDLE		0
#define STAGE_WAIT_P0	1
#define STAGE_CLICK_P0	2
#define STAGE_WAIT_P1	3
#define STAGE_CLICK_P1	4
#define STAGE_WAIT_P2	5
#define STAGE_CLICK_P2	6

#define BTN_HOLD_TIME 100 // 1sec

// EEPROM variables
uint8_t EEMEM eeXMul[4];
uint8_t EEMEM eeYMul[4];

volatile uint8_t calibrationStage;
volatile GTPoint calibratePoints[3];

volatile uint16_t holdCounter;
volatile float xMul;
volatile float yMul;


uint16_t adjust(uint16_t raw, float mul) {
	if(mul == 1.0F) {
		return raw;
	}
	return raw * mul;
}

uint16_t diff(uint16_t one, uint64_t other) {
	if(one > other) {
		return one - other;
	}
	return other - one;
}

void Calibrator_init() {
	// IO
	CALIBRATE_DDR |= 1 << CALIBRATE_PIN_LED; // led as output
	CALIBRATE_DDR &= ~(1 << CALIBRATE_PIN_BTN); // btn as input
	CALIBRATE_PORT |= 1 << CALIBRATE_PIN_BTN; // btn pull-up
	
	// Read Calibration Info
	xMul = eeprom_read_float(&eeXMul);
	yMul = eeprom_read_float(&eeYMul); 
	if(xMul < 1 || yMul < 1 || xMul > 100 || yMul > 100) { // not a valid value
		volatile GTInfo* info = Goodix_readInfo();
		xMul = LOGICAL_MAX_X / info->xResolution;
		yMul = LOGICAL_MAX_Y / info->yResolution;
	}
}

bool Calibrator_adjust(int8_t contacts, GTPoint *points) {
	if(calibrationStage == STAGE_IDLE) {
		for (uint8_t i = 0; i < contacts; i++) {
			points[i].x = adjust(points[i].x, xMul);
			points[i].y = adjust(points[i].y, yMul);
		}
		return true;
	} 
	
	// led notification (turn off when pressed)
	if(contacts == 0) {
		CALIBRATE_PORT |= 1 << CALIBRATE_PIN_LED;
		} else {
		CALIBRATE_PORT &= ~(1 << CALIBRATE_PIN_LED);
	}
	switch(calibrationStage) {
		case STAGE_WAIT_P0: //		#1
			if(contacts > 0) {
				calibrationStage = STAGE_CLICK_P0;
				calibratePoints[0] = points[0];
			}
			break;
		case STAGE_CLICK_P0: //		#2
			if(contacts == 0) {
				calibrationStage = STAGE_WAIT_P1;
			} else {
				calibratePoints[0] = points[0];
			}
			break;
		case STAGE_WAIT_P1: //		#3
			if(contacts > 0) {
				calibrationStage = STAGE_CLICK_P1;
				calibratePoints[1] = points[0];
			}
			break;
		case STAGE_CLICK_P1: //		#4
			if(contacts == 0) {
				calibrationStage = STAGE_WAIT_P2;
			} else {
				calibratePoints[1] = points[0];
			}
			break;
		case STAGE_WAIT_P2: //		#5
			if(contacts > 0) {
				calibrationStage = STAGE_CLICK_P2;
				calibratePoints[2] = points[0];
			}
			break;
		case STAGE_CLICK_P2: //		#6
			if(contacts == 0) {
				calibrateEnd();
			} else {
				calibratePoints[2] = points[0];
			}
			break;
	}
	return false;
}

void Calibrator_tic() {
	if(CALIBRATE_IN & (1 << CALIBRATE_PIN_BTN)) {
		holdCounter = 0;
	} else if(holdCounter < BTN_HOLD_TIME){
		holdCounter += 1;
	} else if(calibrationStage == STAGE_IDLE) {
		calibrateStart();
	}
}

void calibrateStart() {
	CALIBRATE_PORT |= 1 << CALIBRATE_PIN_LED; // led notification
	calibrationStage = STAGE_WAIT_P0;
}

void calibrateEnd() {
	volatile uint16_t physicalWidth = diff(calibratePoints[0].x, calibratePoints[1].x);
	xMul = LOGICAL_MAX_X / physicalWidth;
	eeprom_update_float(&eeXMul, xMul);
	
	volatile uint16_t physicalHeight = diff(calibratePoints[1].y, calibratePoints[2].y);
	yMul = LOGICAL_MAX_Y / physicalHeight;
	eeprom_update_float(&eeYMul, yMul);
	
	CALIBRATE_PORT &= ~(1 << CALIBRATE_PIN_LED); // led notification
	calibrationStage = STAGE_IDLE;
}
