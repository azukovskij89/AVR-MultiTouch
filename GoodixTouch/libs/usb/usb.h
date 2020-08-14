/*
 * usb.h
 *
 * Created: 8/13/2020 10:46:29
 *  Author: azuko
 */ 


#ifndef USB_H_
#define USB_H_

#include "Descriptors.h"

//--------------------------------------------------------------------------------
// Digitizer Device Page Feature Report (Device <-> Host)
//--------------------------------------------------------------------------------
typedef struct
{
	// Collection: TouchScreen
	uint8_t  ContactCountMaximum;						// Usage 0x000D0055: Contact Count Maximum, Value = 0 to 8
} USB_DigitizerFeature_Data_t;

//--------------------------------------------------------------------------------
// Digitizer Device Page Input Report (Device --> Host)
//--------------------------------------------------------------------------------
typedef struct
{
	// Collection: TouchScreen Finger(0)
	uint8_t  Finger0_TipSwitch : 1;                     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  Finger0_InRange : 1;                       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  Finger0_ContactIdentifier;                 // Usage 0x000D0051: Contact Identifier, Value = 0 to 5
	uint16_t Finger0_X;                                 // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t Finger0_Y;                                 // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen Finger(1)
	uint8_t  Finger1_TipSwitch : 1;                     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  Finger1_InRange : 1;                       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  Finger1_ContactIdentifier;                 // Usage 0x000D0051: Contact Identifier, Value = 0 to 5
	uint16_t Finger1_X;                                 // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t Finger1_Y;                                 // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen Finger(2)
	uint8_t  Finger2_TipSwitch : 1;                     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  Finger2_InRange : 1;                       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  Finger2_ContactIdentifier;                 // Usage 0x000D0051: Contact Identifier, Value = 0 to 5
	uint16_t Finger2_X;                                 // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t Finger2_Y;                                 // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen Finger(3)
	uint8_t  Finger3_TipSwitch : 1;                     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  Finger3_InRange : 1;                       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  Finger3_ContactIdentifier;                 // Usage 0x000D0051: Contact Identifier, Value = 0 to 5
	uint16_t Finger3_X;                                 // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t Finger3_Y;                                 // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen Finger(4)
	uint8_t  Finger4_TipSwitch : 1;                     // Usage 0x000D0042: Tip Switch, Value = 0 to 1
	uint8_t  Finger4_InRange : 1;                       // Usage 0x000D0032: In Range, Value = 0 to 1
	uint8_t  Finger4_ContactIdentifier;                 // Usage 0x000D0051: Contact Identifier, Value = 0 to 5
	uint16_t Finger4_X;                                 // Usage 0x00010030: X, Value = 0 to 32767
	uint16_t Finger4_Y;                                 // Usage 0x00010031: Y, Value = 0 to 32767
	// Collection: TouchScreen
	uint8_t  ContactCount;                              // Usage 0x000D0054: Contact Count, Value = 0 to 8
} USB_DigitizerReport_Data_t;


//--------------------------------------------------------------------------------
// Public Methods
//--------------------------------------------------------------------------------
void USB_setHIDCreateHandler(bool (*handler)(USB_DigitizerReport_Data_t*));
void USB_init();
void USB_loop();

#endif /* USB_H_ */