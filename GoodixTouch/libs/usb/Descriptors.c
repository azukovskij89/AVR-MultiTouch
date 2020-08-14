/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM DigitizerReport[] =
{	
	0x05, 0x0D, 			// Usage Page (Digitizer)
	0x09, 0x04, 			// Usage (Touch Screen)
	0xA1, 0x01, 			// Collection (Application)
	0x85, 0x01, 			//     Report ID (1)
	0x09, 0x22, 			//     Usage (Finger)
	0xA1, 0x02, 			//     Collection (Logical)
	0x05, 0x0D, 			//         Usage Page (Digitizer)
	0x09, 0x42, 			//         Usage (Tip Switch)
	0x09, 0x32, 			//         Usage (In Range)
	0x15, 0x00, 			//         Logical Minimum (0)
	0x25, 0x01, 			//         Logical Maximum (1)
	0x95, 0x02, 			//         Report Count (2)
	0x75, 0x01, 			//         Report Size (1)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x06, 			//         Report Count (6)
	0x81, 0x03, 			//         Input (Cnst,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x09, 0x51, 			//         Usage (Contact Identifier)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x08, 			//         Report Size (8)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x05, 0x01, 			//         Usage Page (Generic Desktop)
	0x26, 0xFF, 0x07,       //         Logical Maximum (2047)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x10, 			//         Report Size (16)
	0x55, 0x0E, 			//         Unit Exponent (-2)
	0x65, 0x11, 			//         Unit (SI Lin: Length (cm))
	0x09, 0x30, 			//         Usage (X)
	0x35, 0x00, 			//         Physical Minimum (0)
	0x46, 0xB1, 0x08, 	    //         Physical Maximum (2225)
	0x81, 0x02, 		   	//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x46, 0xE3, 0x04, 	    //         Physical Maximum (1251)
	0x09, 0x31, 			//         Usage (Y)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   //     End Collection
	0xA1, 0x02, 			//     Collection (Logical)
	0x05, 0x0D, 			//         Usage Page (Digitizer)
	0x09, 0x42, 			//         Usage (Tip Switch)
	0x09, 0x32, 			//         Usage (In Range)
	0x15, 0x00, 			//         Logical Minimum (0)
	0x25, 0x01, 			//         Logical Maximum (1)
	0x95, 0x02, 			//         Report Count (2)
	0x75, 0x01, 			//         Report Size (1)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x06, 			//         Report Count (6)
	0x81, 0x03, 			//         Input (Cnst,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x09, 0x51, 			//         Usage (Contact Identifier)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x08, 			//         Report Size (8)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x05, 0x01, 			//         Usage Page (Generic Desktop)
	0x26, 0xFF, 0x07,       //         Logical Maximum (2047)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x10, 			//         Report Size (16)
	0x55, 0x0E, 			//         Unit Exponent (-2)
	0x65, 0x11, 			//         Unit (SI Lin: Length (cm))
	0x09, 0x30, 			//         Usage (X)
	0x35, 0x00, 			//         Physical Minimum (0)
	0x46, 0xB1, 0x08, 	    //         Physical Maximum (2225)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x46, 0xE3, 0x04, 	    //         Physical Maximum (1251)
	0x09, 0x31, 			//         Usage (Y)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   //     End Collection
	0xA1, 0x02, 			//     Collection (Logical)
	0x05, 0x0D, 			//         Usage Page (Digitizer)
	0x09, 0x42, 			//         Usage (Tip Switch)
	0x09, 0x32, 			//         Usage (In Range)
	0x15, 0x00, 			//         Logical Minimum (0)
	0x25, 0x01, 			//         Logical Maximum (1)
	0x95, 0x02, 			//         Report Count (2)
	0x75, 0x01, 			//         Report Size (1)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x06, 			//         Report Count (6)
	0x81, 0x03, 			//         Input (Cnst,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x09, 0x51, 			//         Usage (Contact Identifier)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x08, 			//         Report Size (8)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x05, 0x01, 			//         Usage Page (Generic Desktop)
	0x26, 0xFF, 0x07,       //         Logical Maximum (2047)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x10, 			//         Report Size (16)
	0x55, 0x0E, 			//         Unit Exponent (-2)
	0x65, 0x11, 			//         Unit (SI Lin: Length (cm))
	0x09, 0x30, 			//         Usage (X)
	0x35, 0x00, 			//         Physical Minimum (0)
	0x46, 0xB1, 0x08, 	    //         Physical Maximum (2225)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x46, 0xE3, 0x04, 	    //         Physical Maximum (1251)
	0x09, 0x31, 			//         Usage (Y)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   //     End Collection
	0xA1, 0x02, 			//     Collection (Logical)
	0x05, 0x0D, 			//         Usage Page (Digitizer)
	0x09, 0x42, 			//         Usage (Tip Switch)
	0x09, 0x32, 			//         Usage (In Range)
	0x15, 0x00, 			//         Logical Minimum (0)
	0x25, 0x01, 			//         Logical Maximum (1)
	0x95, 0x02, 			//         Report Count (2)
	0x75, 0x01, 			//         Report Size (1)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x06, 			//         Report Count (6)
	0x81, 0x03, 			//         Input (Cnst,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x09, 0x51, 			//         Usage (Contact Identifier)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x08, 			//         Report Size (8)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x05, 0x01, 			//         Usage Page (Generic Desktop)
	0x26, 0xFF, 0x07,       //         Logical Maximum (2047)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x10, 			//         Report Size (16)
	0x55, 0x0E, 			//         Unit Exponent (-2)
	0x65, 0x11, 			//         Unit (SI Lin: Length (cm))
	0x09, 0x30, 			//         Usage (X)
	0x35, 0x00, 			//         Physical Minimum (0)
	0x46, 0xB1, 0x08, 	    //         Physical Maximum (2225)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x46, 0xE3, 0x04, 	    //         Physical Maximum (1251)
	0x09, 0x31, 			//         Usage (Y)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   //     End Collection
	0xA1, 0x02, 			//     Collection (Logical)
	0x05, 0x0D, 			//         Usage Page (Digitizer)
	0x09, 0x42, 			//         Usage (Tip Switch)
	0x09, 0x32, 			//         Usage (In Range)
	0x15, 0x00, 			//         Logical Minimum (0)
	0x25, 0x01, 			//         Logical Maximum (1)
	0x95, 0x02, 			//         Report Count (2)
	0x75, 0x01, 			//         Report Size (1)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x06, 			//         Report Count (6)
	0x81, 0x03, 			//         Input (Cnst,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x09, 0x51, 			//         Usage (Contact Identifier)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x08, 			//         Report Size (8)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x05, 0x01, 			//         Usage Page (Generic Desktop)
	0x26, 0xFF, 0x07,       //         Logical Maximum (2047)
	0x95, 0x01, 			//         Report Count (1)
	0x75, 0x10, 			//         Report Size (16)
	0x55, 0x0E, 			//         Unit Exponent (-2)
	0x65, 0x11, 			//         Unit (SI Lin: Length (cm))
	0x09, 0x30, 			//         Usage (X)
	0x35, 0x00, 			//         Physical Minimum (0)
	0x46, 0xB1, 0x08, 	    //         Physical Maximum (2225)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x46, 0xE3, 0x04, 	    //         Physical Maximum (1251)
	0x09, 0x31, 			//         Usage (Y)
	0x81, 0x02, 			//         Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   //   End Collection
	0x05, 0x0D, 			//     Usage Page (Digitizer)
	0x09, 0x54, 			//     Usage (Contact Count)
	0x95, 0x01, 			//     Report Count (1)
	0x75, 0x08, 			//     Report Size (8)
	0x25, 0x05, 			//     Logical Maximum (5)
	0x81, 0x02, 			//     Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0x85, 0x02, 			//     Report ID (2)
	0x09, 0x55, 			//     Usage (Contact Count Maximum)
	0xB1, 0x02, 			//     Feature (Data,Var,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
	0xC0,                   // End Collection
	0x05, 0x0C, 			// Usage Page (Consumer Devices)
	0x09, 0x01, 			// Usage (Consumer Control)
	0xA1, 0x01, 			// Collection (Application)
	0x85, 0x04, 			//     Report ID (4)
	0x95, 0x01, 			//     Report Count (1)
	0x75, 0x10, 			//     Report Size (16)
	0x16, 0x00, 0x00, 	    //     Logical Minimum (0)
	0x26, 0x9C, 0x02, 	    //     Logical Maximum (668)
	0x05, 0x0C, 			//     Usage Page (Consumer Devices)
	0x1A, 0x00, 0x00, 	    //     Usage Minimum (Undefined)
	0x2A, 0x9C, 0x02, 	    //     Usage Maximum (AC Distribute Vertically)
	0x81, 0x00, 			//     Input (Data,Ary,Abs)
	0xC0,                   // End Collection
	0x05, 0x01, 			// Usage Page (Generic Desktop)
	0x09, 0x80, 			// Usage (System Control)
	0xA1, 0x01, 			// Collection (Application)
	0x85, 0x05, 			//     Report ID (5)
	0x75, 0x01, 			//     Report Size (1)
	0x95, 0x08, 			//     Report Count (8)
	0x15, 0x00, 			//     Logical Minimum (0)
	0x25, 0x01, 			//     Logical Maximum (1)
	0x09, 0x81, 			//     Usage (System Power Down)
	0x09, 0x82, 			//     Usage (System Sleep)
	0x09, 0x83, 			//     Usage (System Wake Up)
	0x09, 0x84, 			//     Usage (System Context Menu)
	0x09, 0x85, 			//     Usage (System Main Menu)
	0x09, 0x86, 			//     Usage (System App Menu)
	0x09, 0x87, 			//     Usage (System Menu Help)
	0x09, 0x88, 			//     Usage (System Menu Exit)
	0x81, 0x02, 			//     Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
	0xC0,                   // End Collection
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(1, 1, 0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03EB,
	.ProductID              = 0x2064,
	.ReleaseNumber          = VERSION_BCD(0, 0, 1),

	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = USE_INTERNAL_SERIAL,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_REMOTEWAKEUP),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0,
			.AlternateSetting       = 0,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_DigitizerHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(01, 1, 1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(DigitizerReport)
		},

	.HID_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = MOUSE_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = MOUSE_EPSIZE,
			.PollingIntervalMS      = 0x0A
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(6), .Type = DTYPE_String},

	.UnicodeString          = L"NoName"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(9), .Type = DTYPE_String},

	.UnicodeString          = L"TWI-Touch"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, 
	const void** const DescriptorAddress) {
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}

			break;
		case HID_DTYPE_HID:
			Address = &ConfigurationDescriptor.HID_DigitizerHID;
			Size    = sizeof(USB_HID_Descriptor_HID_t);
			break;
		case HID_DTYPE_Report:
			Address = &DigitizerReport;
			Size    = sizeof(DigitizerReport);
			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

