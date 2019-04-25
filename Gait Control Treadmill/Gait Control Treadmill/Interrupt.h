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
	PINB |= (1<<PINB4);
}
ISR(TIMER0_COMPB_vect){
	PINB |= (1<<PINB4);
}

ISR(TIM1_OVF_vect){
    // increment
    sensors[0].timer += 65535;
}
ISR(TIM3_OVF_vect){
    // increment
    sensors[1].timer += 65535;
}
ISR(TIM4_OVF_vect){
    // increment
    sensors[2].timer += 65535;
}

ISR(INT0_vect){
	LED_TOGGLE;
    /*if (PIND & (1<<PORTD2)) {
        // rising edge: start timer1(16-bit)
        TCCR1B |= (1<<CS10);
        // set overflow interrupt flag
        TIMSK1 |= (1<<TOIE1);
    }
    else {
        // falling edge: stop timer
        TCCR1B &= ~(1<<CS10);
        // calculate time passed
        sensors[0].timer += TCNT1;
        // reset counter
        TCNT1 = 0;
        // set flag
        sensors[0].echoDone = 1;
    }*/
}

ISR(INT1_vect){
	if (PIND & (1<<PORTD3)){
        // rising edge: start timer3(16-bit)
        TCCR3B |= (1<<CS30);

        TIMSK3 |= (1<<TOIE3);
	}
	else{
        // falling edge: stop timer
        TCCR3B &= ~(1<<CS30);
        // calculate time passed
        sensors[1].timer += TCNT3;
        // reset counter
        TCNT3 = 0;
        // set flag
        sensors[1].echoDone = 1;
	}
}

ISR(PCINT0_vect){
    if (PINB & (1<<PORTB4)){
        // rising edge: start timer3(16-bit)
        TCCR4B |= (1<<CS40);
        
        TIMSK4 |= (1<<TOIE4);
    }
    else{
        // falling edge: stop timer
        TCCR4B &= ~(1<<CS40);
        // calculate time passed
        sensors[2].timer += TCNT4;
        // reset counter
        TCNT4 = 0;
        // set flag
        sensors[2].echoDone = 1;
    }
}

#endif /* INTERRUPT_H_ */
