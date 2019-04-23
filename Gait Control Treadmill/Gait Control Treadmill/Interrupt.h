/*
 * Interrupt.h
 *
 * Created: 2019/4/23 1:04:52
 *  Author: User
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "Sensor.h"

ISR(TIMER0_COMPA_vect){
	LED_ON;
}
ISR(TIMER0_COMPB_vect){
	LED_OFF;
}

ISR(INT0_vect){
	if (sensors[0].flag == 1){
		TCCR1B = 0;
		sensors[0].pulse = TCNT1;
		TCNT1 = 0;
		sensors[0].flag = 0;
	}
	if (sensors[0].flag == 0){
		TCCR1B |= (1<<CS10);
		sensors[0].flag = 1;
	}
}

ISR(INT1_vect){
	if (sensors[1].flag == 1){
		//LED_TOGGLE;
		TCCR3B = 0;
		sensors[1].pulse = TCNT3;
		TCNT3 = 0;
		sensors[1].flag = 0;
	}
	if (sensors[1].flag == 1){
		//LED_TOGGLE;
		TCCR3B |= (1<<CS10);
		sensors[1].flag = 1;
	}
}
ISR(PCINT0_vect){
	if (sensors[2].flag == 1){
		//LED_TOGGLE;
		TCCR4B = 0;
		sensors[2].pulse = TCNT4;
		TCNT4 = 0;
		sensors[2].flag = 0;
	}
	if (sensors[2].flag == 1){
		//LED_TOGGLE;
		TCCR4B |= (1<<CS10);
		sensors[2].flag = 1;
	}
}

#endif /* INTERRUPT_H_ */