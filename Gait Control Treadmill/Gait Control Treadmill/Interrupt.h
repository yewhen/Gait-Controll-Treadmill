/*
 * Interrupt.h
 *
 * Created: 2019/4/23 1:04:52
 *  Author: User
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdio.h>
#include "Sensor.h"
#include "USART.h"
#define LED_TOGGLE			PINB |= (1<<PINB5)

ISR(TIMER0_COMPA_vect){
	//LED_ON;
}
ISR(TIMER0_COMPB_vect){
	//LED_OFF;
}

/*ISR(INT0_vect){
	if (sensors[0].flag == 1){
		TCCR1B = 0;
		sensors[0].pulse = TCNT1;
		TCNT1 = 0;
		char s[5];
		char space[] = "  ";
		sprintf(s, "%d", sensors[1].flag);
		USART_putstring(s);
		sensors[0].flag = 0;
	}
	if (sensors[0].flag == 0){
		PORTB |= (1<<PORTB5);
		TCCR1B |= (1<<CS10);
		char s[5];
		char space[] = "  ";
		sprintf(s, "%d", sensors[1].flag);
		USART_putstring(s);
		sensors[0].flag = 1;

	}
	LED_TOGGLE;
	//_delay_ms(10000);
}*/

/*ISR(INT1_vect){
	LED_TOGGLE;
	//_delay_ms(10000);
	if (sensors[1].flag == 1){
		//TCCR3B = 0;
		//sensors[1].pulse = TCNT3;
		//TCNT3 = 0;
		char s[5];
		char space[] = "  ";
		sprintf(s, "%d", sensors[1].flag);
		USART_putstring(s);
		sensors[1].flag = 0;
	}
	if (sensors[1].flag == 0){
		//TCCR3B |= (1<<CS30);
		char s[5];
		char space[] = "  ";
		sprintf(s, "%d", sensors[1].flag);
		USART_putstring(s);
		sensors[1].flag = 1;

	}
}*/
ISR(PCINT0_vect){
	if (sensors[2].flag == 1){
		TCCR4B = 0;
		sensors[2].pulse = TCNT4;
		TCNT4 = 0;
		sensors[2].flag = 0;
	}
	if (sensors[2].flag == 0){
		TCCR4B |= (1<<CS40);
		sensors[2].flag = 1;
	}
}

#endif /* INTERRUPT_H_ */