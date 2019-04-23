/*
 * PWM.h
 *
 * Created: 2019/4/23 0:50:36
 *  Author: User
 */ 


#ifndef PWM_H_
#define PWM_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU				16000000UL // 16MHz
#define FREQ				5000
#define PRESCALE			64
#define LED_ON				PORTB |= (1<<PORTB5)
#define LED_OFF				PORTB &= ~(1<<PORTB5)
#define LED_TOGGLE			PINB |= (1<<PINB5)

void PWM_Init_16();
void PWM_Init_8();
void PWM_Increase_duty_8();
void PWM_Decrease_duty_8();


#endif /* PWM_H_ */