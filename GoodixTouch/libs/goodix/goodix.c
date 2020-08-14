#include "goodix.h"
#include <util/twi.h>

#include <avr/interrupt.h>
#include <util/delay.h>
#include "../wire/wire.h"
#include "../../io.h"

// Variables
uint8_t i2cAddr;
struct GTConfig config;
struct GTInfo info;
uint8_t points[GOODIX_MAX_CONTACTS*GOODIX_CONTACT_SIZE]; //points buffer
void (*touchHandler)(int8_t, GTPoint*);


//----- Utils -----
void i2cStart(uint16_t reg) {
	Wire_beginTransmission(i2cAddr);
	Wire_write(((uint8_t) ((reg) >> 8)));
	Wire_write((uint8_t) ((reg) & 0xff));
}

void i2cRestart() {
	Wire_endTransmission(false);
	Wire_beginTransmission(i2cAddr);
}

uint8_t i2cStop() {
	return Wire_endTransmission(true);
}

uint8_t writearray(uint16_t reg, uint8_t *buf, size_t len) {
	uint8_t error;
	uint16_t startPos = 0;

	while (startPos < len) {
		i2cStart(reg + startPos);
		startPos += Wire_writearray(buf + startPos, len - startPos);
		error = Wire_endTransmission(true);
		if (error)
		return error;
	}
	return 0;
}

uint8_t write(uint16_t reg, uint8_t buf) {
	i2cStart(reg);
	Wire_write(buf);
	return Wire_endTransmission(true);
}

static uint8_t read(uint16_t reg, uint8_t *buf, size_t len) {
	uint8_t res;

	i2cStart(reg);

	res = Wire_endTransmission(false);
	if (res != GOODIX_OK) {
		return res;
	}

	uint16_t pos = 0, prevPos = 0;
	size_t readLen = 0;
	uint8_t maxErrs = 3;

	while (pos < len) {
		readLen = Wire_requestFrom(i2cAddr, (len - pos), 0, 0, 1);

		prevPos = pos;
		while (Wire_available()) {
			buf[pos] = Wire_read();
			pos++;
		}

		if (prevPos == pos)
		maxErrs--;

		if (maxErrs <= 0) {
			break;
		}
		_delay_ms(0);
	}
	return 0;
}

// Interrupt handling
volatile uint8_t goodixIRQ = 0;
ISR(INT3_vect) { // PD3 pin
	goodixIRQ = 1;
}

void Goodix_setHandler(void (*handler)(int8_t, GTPoint*)) {
  touchHandler = handler;
}

uint8_t Goodix_begin() {
	// Configure TWI
	Wire_setClock(400000);
	Wire_begin();
	
	_delay_ms(300);

	// Configure interrupts
	EICRA |= (1 << ISC01) | (1 << ISC00); // rising edge
	EIMSK |= (1 << INT3);  // PD3 pin
	i2cAddr = GOODIX_I2C_ADDR_BA;

	// Take chip some time to start
	_delay_ms(300);
	uint8_t result = Goodix_reset();
	_delay_ms(200);

	return result;
}

uint8_t Goodix_reset() {
	_delay_ms(1);

	GOODIX_DDR |= (1 << GOODIX_PIN_INT);
	GOODIX_DDR |= (1 << GOODIX_PIN_RST);

	GOODIX_PORT &= ~(1 << GOODIX_PIN_INT);
	GOODIX_PORT &= ~(1 << GOODIX_PIN_RST);

	/* begin select I2C slave addr */

	/* T2: > 10ms */
	_delay_ms(11);

	/* HIGH: 0x28/0x29 (0x14 7bit), LOW: 0xBA/0xBB (0x5D 7bit) */
	if (i2cAddr == GOODIX_I2C_ADDR_28) {	
		GOODIX_PORT |= (1 << GOODIX_PIN_INT);
	} else {
		GOODIX_PORT &= ~(1 << GOODIX_PIN_INT);
	}

	/* T3: > 100us */
	_delay_us(110);
	GOODIX_DDR &= ~(1 << GOODIX_PIN_RST);
	//if ((GOODIX_IN & (1 << pin)) == 0)
	//  return false;

	/* T4: > 5ms */
	_delay_ms(6);
	GOODIX_PORT &= ~(1 << GOODIX_PIN_INT);
	/* end select I2C slave addr */

	/* T5: 50ms */
	_delay_ms(51);
	GOODIX_DDR &= ~(1 << GOODIX_PIN_INT); // INT pin has no pullups so simple set to floating input

	sei();

	return 1;
}

void Goodix_loop() {
	uint8_t irq = goodixIRQ;
	goodixIRQ = 0;

	if (irq) {
		onIRQ();
	}
}

/**
   Read goodix touchscreen version
   set 4 chars + zero productID to target
*/
uint8_t Goodix_productID(char *target) {
	uint8_t error;
	uint8_t buf[4];

	error = read(GOODIX_REG_ID, buf, 4);
	if (error) {
		return error;
	}

	memcpy(target, buf, 4);
	target[4] = 0;

	return 0;
}

/**
   goodix_i2c_test - I2C test function to check if the device answers.

   @client: the i2c client
*/
uint8_t Goodix_test() {
  uint8_t testByte;
  return read(GOODIX_REG_CONFIG_DATA,  &testByte, 1);
}

uint8_t Goodix_calcChecksum(uint8_t* buf, uint8_t len) {
  uint8_t ccsum = 0;
  for (uint8_t i = 0; i < len; i++) {
    ccsum += buf[i];
  }
  //ccsum %= 256;
  ccsum = (~ccsum) + 1;
  return ccsum;
}

uint8_t Goodix_readChecksum() {
  uint16_t aStart = GT_REG_CFG;
  uint16_t aStop = 0x80FE;
  uint8_t len = aStop - aStart + 1;
  uint8_t buf[len];

  read(aStart, buf, len);
  return calcChecksum(buf, len);
}

uint8_t Goodix_fwResolution(uint16_t maxX, uint16_t maxY) {
  uint8_t len = 0x8100 - GT_REG_CFG + 1;
  uint8_t cfg[len];
  read(GT_REG_CFG, cfg, len);

  cfg[1] = (maxX & 0xff);
  cfg[2] = (maxX >> 8);
  cfg[3] = (maxY & 0xff);
  cfg[4] = (maxY >> 8);
  cfg[len - 2] = calcChecksum(cfg, len - 2);
  cfg[len - 1] = 1;

  writearray(GT_REG_CFG, cfg, len);
}

GTConfig* Goodix_readConfig() {
  read(GT_REG_CFG, (uint8_t *) &config, sizeof(config));
  return &config;
}

GTInfo* Goodix_readInfo() {
  read(GT_REG_DATA, (uint8_t *) &info, sizeof(config));
  return &info;
}

void onIRQ() {
  //uint8_t buf[1 + GOODIX_CONTACT_SIZE * GOODIX_MAX_CONTACTS];
  int8_t contacts;

  contacts = Goodix_readInput(points);
  if (contacts < 0)
    return;

  touchHandler(contacts, (GTPoint *)points);

  write(GOODIX_READ_COORD_ADDR, 0);
}


#define EAGAIN 100 // Try again error
int16_t Goodix_readInput(uint8_t *data) {
  int touch_num;
  int error;

  uint8_t regState[1];

  error = read(GOODIX_READ_COORD_ADDR, regState, 1);
  //log_printf("regState: %#06x\n", regState);

  if (error) {
    //dev_err(&ts->client->dev, "I2C transfer error: %d\n", error);
    return -error;
  }

  if (!(regState[0] & 0x80))
    return -EAGAIN;

  touch_num = regState[0] & 0x0f;
  //if (touch_num > ts->max_touch_num)
  //  return -EPROTO;

  //log_printf("touch num: %d\n", touch_num);

  if (touch_num > 0) {
    /*    data += 1 + GOODIX_CONTACT_SIZE;
        error = read(GOODIX_READ_COORD_ADDR + 1 + GOODIX_CONTACT_SIZE, data,
              GOODIX_CONTACT_SIZE * (touch_num - 1));
    */
    error = read(GOODIX_READ_COORD_ADDR + 1, data, GOODIX_CONTACT_SIZE * (touch_num));

    if (error)
      return -error;
  }

  return touch_num;
}
