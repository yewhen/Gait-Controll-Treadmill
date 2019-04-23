/*
 * Gait Control Treadmill.c
 *
 * Created: 2019/4/23 0:49:17
 * Author : User
 */ 

#include "PWM.h"
#include "USART.h"
#include "Interrupt.h"
#include <stdio.h>

#define BAUD				9600
#define MYUBBR				F_CPU/16/BAUD-1



int main(){
	Sensor_Init();
	USART_Init(MYUBBR);
	
	char s2[] = "hello";

    //PWM_Init_8();
	sei();
	char space[] = "  ";
	int prev = 0, cur = 0;
    while (1){
		char s[5];
		
		
		//int idx;
		// Trig Signal
		PORTB |= (1<<PINB3); 
		_delay_us(15); 
		PORTB &= ~(1<<PINB3);
		
		cur = sensors[0].pulse / 58;
		if (cur <= 2 || cur >= 400) continue;
		sprintf(s, "%d", cur);
		USART_putstring(s);
		USART_putstring(space);
		_delay_ms(1000);
		/*for (idx = 0; idx < NUM_SENSOR; idx++){
		
		
		}*/
		//cur = sensors[0].pulse/58;
	}
	return 0;
}


