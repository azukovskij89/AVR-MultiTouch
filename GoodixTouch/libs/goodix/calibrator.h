/*
 * calibrator.h
 *
 * Created: 8/14/2020 12:12:02
 *  Author: azuko
 */ 


#ifndef CALIBRATOR_H_
#define CALIBRATOR_H_

#include <stdbool.h>

void Calibrator_init();

bool Calibrator_adjust(int8_t contacts, GTPoint *points);

void Calibrator_tic();

#endif /* CALIBRATOR_H_ */