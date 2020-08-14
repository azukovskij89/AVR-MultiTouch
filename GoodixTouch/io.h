/*
 * io.h
 *
 * Created: 8/12/2020 21:58:19
 *  Author: azuko
 */ 


#ifndef IO_H_
#define IO_H_

#include <avr/io.h>

#define TWI_PORT PORTD
#define TWI_PIN_SDA PORTD2
#define TWI_PIN_SCL PORTD3

#define GOODIX_DDR DDRD
#define GOODIX_IN PIND
#define GOODIX_PORT TWI_PORT
#define GOODIX_PIN_INT PORTD3
#define GOODIX_PIN_RST PORTD2

#define CALIBRATE_DDR DDRD
#define CALIBRATE_IN PIND
#define CALIBRATE_PORT PORTD
#define CALIBRATE_PIN_BTN PORTD4
#define CALIBRATE_PIN_LED PORTD5

#endif /* IO_H_ */