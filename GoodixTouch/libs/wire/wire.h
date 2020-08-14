/*
 * Wire.h
 *
 * Created: 8/12/2020 20:43:37
 *  Author: azuko
 */ 

#include <stdint.h>
#include <stddef.h>

#ifndef WIRE_H_
#define WIRE_H_
	
	void Wire_begin();
	void Wire_setClock(uint32_t);
	uint8_t Wire_requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
	int Wire_available(void);
	int Wire_read(void);
	size_t Wire_write(uint8_t);
	size_t Wire_writearray(const uint8_t *, size_t);
	void Wire_beginTransmission(uint8_t);
	uint8_t Wire_endTransmission(uint8_t);
	
#endif /* WIRE_H_ */