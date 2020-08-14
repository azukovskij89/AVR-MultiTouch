/*
 * descriptor.h
 *
 * Created: 8/13/2020 01:06:28
 *  Author: azuko
 */ 


#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include <LUFA/Drivers/USB/USB.h>
#include <LUFAConfig.h>



//--------------------------------------------------------------------------------
// Digitizer Device Page featureReport 54 (Device <-> Host)
//--------------------------------------------------------------------------------

typedef struct
{
	uint8_t  reportId;                                 // Report ID = 0x54 (84) 'T'
	// Collection: TouchScreen
	uint8_t  DIG_TouchScreenContactCountMaximum;       // Usage 0x000D0055: Contact Count Maximum, Value = 0 to 8
} featureReport54_t;


//--------------------------------------------------------------------------------
// Digitizer Device Page inputReport 54 (Device --> Host)
//--------------------------------------------------------------------------------

typedef struct
{
	uint8_t  reportId;                                 // Report ID = 0x54 (84) 'T'
	// Collection: TouchScreen Finger
	uint8_t  DIG_TouchScreenFingerTipSwitch : 1;       // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  DIG_TouchScreenFingerInRange : 1;         // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  DIG_TouchScreenFingerConfidence : 1;      // Usage 0x000D0047: Confidence, Value = 0 to 1
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  DIG_TouchScreenFingerContactIdentifier;   // Usage 0x000D0051: Contact Identifier, Value = 0 to 1
	uint16_t GD_TouchScreenFingerX;                    // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t GD_TouchScreenFingerY;                    // Usage 0x00010031: Y, Value = 0 to 32767
	uint8_t  DIG_TouchScreenFingerTipSwitch_1 : 1;     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  DIG_TouchScreenFingerInRange_1 : 1;       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  DIG_TouchScreenFingerConfidence_1 : 1;    // Usage 0x000D0047: Confidence, Value = 0 to 1
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  : 1;                                      // Pad
	uint8_t  DIG_TouchScreenFingerContactIdentifier_1; // Usage 0x000D0051: Contact Identifier, Value = 0 to 1
	uint16_t GD_TouchScreenFingerX_1;                  // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t GD_TouchScreenFingerY_1;                  // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen
	uint8_t  DIG_TouchScreenContactCount;              // Usage 0x000D0054: Contact Count, Value = 0 to 8
} inputReport54_t;

#endif /* DESCRIPTOR_H_ */