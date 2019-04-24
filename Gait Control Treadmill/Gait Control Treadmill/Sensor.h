/*
 * Sensor.h
 *
 * Created: 2019/4/23 0:50:58
 *  Author: User
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NUM_SENSOR		3


struct table{
	volatile int pulse;
	volatile int flag;
	int dist;
	float prev[5];
};
typedef struct table sensor;

int Sensor_Init();
static sensor sensors[NUM_SENSOR];


#endif /* SENSOR_H_ */