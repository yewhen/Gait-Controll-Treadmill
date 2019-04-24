/*
 * Sensor.c
 *
 * Created: 2019/4/23 0:50:19
 *  Author: User
 */ 

#include "sensor.h"
#define LED_TOGGLE			PINB |= (1<<PINB5)


int Sensor_Init(){
	//input(0), output(1)
	int idx;
	// Trig Pin Setup: PB3
	DDRB |= (1<<DDB3); 
	// Echo Pin Setup: PD2(EXTINT0), PD3(EXTINT1), PB5(PCINT0)
	DDRD &= ~(1<<DDD2); 
	//DDRD &= ~(1<<DDD3);
	//DDRB &= ~(1<<DDB4);

	// Turn on the pull-up
	//PORTD |= (1<<PORTD2) | (1<<PORTD3);
	//PORTB |= (1<<PORTB4);
	PORTD &= ~(1<<PORTD2);
	//_delay_ms(50);

	// Enable the Interrupt
	EICRA |= (1<<ISC00) | (1<<ISC10); // Set INT0 & INT1 to trigger on ANY logic change
	EIMSK |= (1<<INT0) | (1<<INT1);  // Turns on INT0 & INT1
	
	//PCICR |= (1<<PCIE0); 
	//PCMSK0 |= (1<<PCINT4);	

	for (idx = 0; idx < NUM_SENSOR; idx++){
		sensors[idx].pulse = 0;
		sensors[idx].flag = 0;
		sensors[idx].dist = 0;
	}
	return 102;
} 