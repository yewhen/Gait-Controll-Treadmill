/*
 * PWM.c
 *
 * Created: 2019/4/23 0:50:26
 *  Author: User
 */ 

#include "PWM.h"
 

void PWM_Increase_duty_8(){
	uint8_t period = OCR0A;
	uint8_t duty = OCR0B;

	if (duty < period) duty++;
	else duty = 0;

	OCR0B = duty;
}
void PWM_Decrease_duty_8(){
	uint8_t duty = OCR0B;

	if (duty > 0) duty--;
	else duty = 0;

	OCR0B = duty;
}
void PWM_Init_16(void){
	TCCR1B |= (1<<CS11) | (1<<WGM12); // CTC mode
	TCCR1B &= ~(1<<CS12);
	TCCR1B &= ~(1<<CS10);
	TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);
	 
	OCR1A = (F_CPU / PRESCALE / FREQ) - 1; // 5KHz
	OCR1B = (F_CPU / PRESCALE / FREQ) * 0.5 - 1;
}

void PWM_Init_8(void){
	TCCR0A |= (1<<WGM01); // CTC mode
	TCCR0B |= (1<<CS01) | (1<<CS00); 
	TCCR0B &= ~(1<<CS02);
	TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B);
	 
	OCR0A = (F_CPU / PRESCALE / FREQ) - 1; // 5KHz
	OCR0B = (F_CPU / PRESCALE / FREQ) * 0.5 - 1;
}