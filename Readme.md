# AVR based Multi-Touch Controller
Avr (atmega32u4) based touch controller that acts as an adapter between I2C touch panel and USB HID-compliant device. 
Based on https://github.com/nik-sharky/arduino-goodix project and was tested on Goodix GT911 panel. 
HID Device supports multi-touch with up to 5 contact points. 

## Calibration
TDevice is calibrated with resolution resolved from Goodix info by default, manual calibration can be triggered using following steps:
1. Hold calibrate switch (PD4/A4) for 1 second until LED turns off
2. On touch screen press on points #1, #2 and #3 to mark screen limits - calibrate led will turn on on each step
![](/img/calibrate.png)
3. After #3 press LED should turn on and stay on again, in case of calibration error start over from step 1.

## Circuit Diagram 
![](/img/schematic.png)

##  Arduino Wiring Diagram
Alternatively fimrware can be uploaded to 3.3v Arduino Pro Micro running at 8 or 16mhz, calibrate button will need to be connected externally:

![](/img/arduino.png)


