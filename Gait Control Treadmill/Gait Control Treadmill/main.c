/*
 * Gait Control Treadmill.c
 *
 * Created: 2019/4/23 0:49:17
 * Author : User
 */ 

#include "PWM.h"
#include "Interrupt.h"

#define BAUD				9600
#define MYUBBR				F_CPU/16/BAUD-1



int main(){
	DDRB |= (1<<DDB5);
	Sensor_Init();
	//char sss[10];
	USART_Init(MYUBBR);
	//sprintf(sss, "%d", a);
	//USART_putstring(sss);
	//char s2[] = "hello";

    //PWM_Init_8();
	sei();
	//char space[] = "  flag:";
	//char question[] = "  ";
	unsigned int cur = 0;
    while (1){
		char s[5];
		//char f[3];
		//int idx;
		// Trig Signal
		PORTB |= (1<<PINB3); 
		_delay_us(10); 
		PORTB &= ~(1<<PINB3);
		
		//_delay_us(15);
		/*do{
			//_delay_ms(500);
			cur = sensors[0].pulse / 58;
			LED_TOGGLE;
		}while (cur <= 2 || cur >= 400);

		//cur = sensors[0].pulse / 58;
		
		sprintf(s, "%u", cur);
		sprintf(f, "%d", sensors[0].flag);
		USART_putstring(s);
		USART_putstring(space);
		USART_putstring(f);
		USART_putstring(question);
		_delay_ms(10000);*/
		/*for (idx = 0; idx < NUM_SENSOR; idx++){
		
		
		}*/
		//cur = sensors[0].pulse/58;
	}
	return 0;
}


