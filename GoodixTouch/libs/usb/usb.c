/*
 * usb.c
 *
 * Created: 8/13/2020 10:47:06
 *  Author: azuko
 */ 

#include "usb.h"


#define CONTACT_POINTS_MAX 5

static uint8_t PrevDigitizerHIDReportBuffer[sizeof(USB_DigitizerReport_Data_t)];

USB_ClassInfo_HID_Device_t Digitizer_HID_Interface =
{
	{
		0,
		{
			MOUSE_EPADDR,
			MOUSE_EPSIZE,
			1,
		},
		PrevDigitizerHIDReportBuffer,
		sizeof(PrevDigitizerHIDReportBuffer),
	},
};

bool (*createHIDHandler)(USB_DigitizerReport_Data_t*);

void USB_setHIDCreateHandler(bool (*handler)(USB_DigitizerReport_Data_t*)) {
	createHIDHandler = handler;
}

void USB_init() {
	USB_Init();
}

void USB_loop() {
	HID_Device_USBTask(&Digitizer_HID_Interface);
	USB_USBTask();
}


/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
//	HID_Device_ProcessControlRequest(&Digitizer_HID_Interface);
	
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Digitizer_HID_Interface);
	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Digitizer_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Digitizer_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	

	if (*ReportID == 0 && ReportType == HID_REPORT_ITEM_In) {
		USB_DigitizerReport_Data_t* DigitizerReport = (USB_DigitizerReport_Data_t*)ReportData;
		*ReportID=0x01;
		*ReportSize=sizeof(USB_DigitizerReport_Data_t);
		return createHIDHandler(DigitizerReport);
	}
	if (*ReportID == 2) {
		USB_DigitizerFeature_Data_t* FeatureReport = (USB_DigitizerFeature_Data_t*)ReportData;
		FeatureReport->ContactCountMaximum = CONTACT_POINTS_MAX;
		*ReportID=0x02;
		*ReportSize=1;
		return false;
	}

	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize) {
}