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

/*int main(){
    char hi[] = "hello world!";
    DDRB |= (1<<DDB5);
    Sensor_Init();
    PWM_Init_8();
    USART_Init(MYUBBR);
    USART_putstring(hi);
    
    // HC-SR04
    DDRB |= (1<<PORTB3);
    DDRD &= ~(1<<PORTD2);
	PORTD |= (1<<PORTD2);
    
    char str[16];
    char space[] = " .";
    int prevDist = 0;

    while (1) {
        // Put the Trig low at first
        PORTB &= ~(1<<PORTB3);
        _delay_us(20);
        
        // Put Trig Pin high at least 10us
        PORTB |= (1 << PORTB3);
        _delay_us(12);
        
        
        int dist = getDistance();
        // sensor only works till 400 cm - if it exceeds, this value just send previous reading
        //if (dist > 400 || dist < 2) dist = prevDist;
        
        sprintf(str, "%d\n", dist);
        USART_putstring(str);
		USART_putstring(space);
        prevDist = dist;
        _delay_ms(70);
    }
    return 0;
}*/

int main(){

	//char s2[] = "hello";
	DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB4);
    PWM_Init_8();
	Sensor_Init();
	USART_Init(MYUBBR);
	sei();
	char space[] = "  ";
	unsigned int cur = 0;
    while (1){
		char s[5];
		PWM_Increase_duty_8();
		_delay_ms(1000);
		//char f[3];
		//int idx;
		// Trig Signal
		PORTB |= (1<<PINB3); 
		_delay_us(10); 
		PORTB &= ~(1<<PINB3);
		
		//_delay_us(15);
		//do{
			//_delay_ms(500);
		cur = sensors[0].timer / 58;
		//LED_TOGGLE;
		//}while (cur <= 2 || cur >= 400);

		//cur = sensors[0].pulse / 58;
		
		sprintf(s, "%u", cur);
		//sprintf(f, "%d", sensors[0].flag);
		USART_putstring(s);
		USART_putstring(space);
		//USART_putstring(f);
		//USART_putstring(question);
		//for (idx = 0; idx < NUM_SENSOR; idx++){
		
		
		//}
		//cur = sensors[0].pulse/58;*/
	}
	return 0;
}


