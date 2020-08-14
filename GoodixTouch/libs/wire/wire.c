/*
 * wire.c
 *
 * Created: 8/12/2020 20:45:25
 *  Author: azuko
 */

#include "wire.h"

#define BUFFER_LENGTH 32

int write_error;

uint8_t rxBuffer[BUFFER_LENGTH];
uint8_t rxBufferIndex = 0;
uint8_t rxBufferLength = 0;

uint8_t txAddress = 0;
uint8_t txBuffer[BUFFER_LENGTH];
uint8_t txBufferIndex = 0;
uint8_t txBufferLength = 0;

uint8_t transmitting = 0;

void onReceiveService(uint8_t* inBytes, int numBytes) {}
void onRequestService(void) {}

void Wire_begin(void) {
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	twi_init();
	twi_attachSlaveTxEvent(onRequestService); // default callback must exist
	twi_attachSlaveRxEvent(onReceiveService); // default callback must exist
}

void Wire_setClock(uint32_t clock) {
	twi_setFrequency(clock);
}

uint8_t Wire_requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop) {
	if (isize > 0) {
		// send internal address; this mode allows sending a repeated start to access
		// some devices' internal registers. This function is executed by the hardware
		// TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)

		Wire_beginTransmission(address);

		// the maximum size of internal address is 3 bytes
		if (isize > 3){
			isize = 3;
		}

		// write internal register address - most significant byte first
		while (isize-- > 0)
		write((uint8_t)(iaddress >> (isize*8)));
		Wire_endTransmission(0);
	}

	// clamp to buffer length
	if(quantity > BUFFER_LENGTH){
		quantity = BUFFER_LENGTH;
	}
	// perform blocking read into buffer
	uint8_t read = twi_readFrom(address, rxBuffer, quantity, sendStop);
	// set rx buffer iterator vars
	rxBufferIndex = 0;
	rxBufferLength = read;

	return read;
}

int Wire_available(void) {
	return rxBufferLength - rxBufferIndex;
}

int Wire_read(void)
{
	int value = -1;
	
	// get each successive byte on each call
	if(rxBufferIndex < rxBufferLength){
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}

	return value;
}

size_t Wire_write(uint8_t data) {
	if(transmitting) {
		// in master transmitter mode
		// don't bother if buffer is full
		if(txBufferLength >= BUFFER_LENGTH){
			write_error = 1;
			return 0;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer
		txBufferLength = txBufferIndex;
	} else {
		// in slave send mode
		// reply to master
		twi_transmit(&data, 1);
	}
	return 1;
}

size_t Wire_writearray(const uint8_t *data, size_t quantity) {
	if(transmitting) {
		// in master transmitter mode
		for(size_t i = 0; i < quantity; ++i){
			write(data[i]);
		}
		} else {
		// in slave send mode
		// reply to master
		twi_transmit(data, quantity);
	}
	return quantity;
}

void Wire_beginTransmission(uint8_t address)
{
	// indicate that we are transmitting
	transmitting = 1;
	// set address of targeted slave
	txAddress = address;
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
}

uint8_t Wire_endTransmission(uint8_t sendStop) {

	// transmit buffer (blocking)
	uint8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return ret;
}