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

int pinEcho = PA0;
char pinTX = PB1;
// 1/0 flag to check if echo is over
volatile char echoDone = 0;
// current timer0 count
uint32_t countTimer1 = 0;

void initHCSR04(){
    // initialize HC-SR04 pins
    // set Trigger pin (connected to PB0) as output
    DDRB |= (1<<PORTB3);
    DDRD &= ~(1<<PORTD2);
}

float getDistanceHCSR04(){
    // Send a 10us HIGH pulse on the Trigger pin.
    // The sensor sends out a “sonic burst” of 8 cycles.
    // Listen to the Echo pin, and the duration of the next HIGH
    // signal will give you the time taken by the sound to go back
    // and forth from sensor to target.
    
    float distance = 0.0f;

    cli();
    // enable interrupt
    EICRA |= (1<<ISC00);
    EIMSK |= (1<<INT0);
    sei();
    
    // set echo flag & reset counter
    echoDone = 0;
    countTimer1 = 0;
    
    // send 10us trigger pulse
    PORTB &= ~(1 << PORTB3);
    _delay_us(20);
    
    PORTB |= (1 << PORTB3);
    _delay_us(12);
    PORTB &= ~(1 << PORTB3);
    _delay_us(20);
    
    // listen for echo and time it
    // loop till echo pin goes low
    while(!echoDone);
    
    // disable pin-change interrupt:
    // disable interrupt
    EICRA &= ~(1<<ISC00);
    EIMSK &= ~(1<<INT0);
    
    // calculate duration
    float duration = countTimer1/16000000.0;
    
    // dist = duration * speed of sound * 1/2
    // dist in cm = duration in s * 340.26 * 100 * 1/2
    // = 17013*duration
    distance = 17013.0 * duration;
    
    return distance;
}

// timer0 overflow interrupt
ISR(TIM1_OVF_vect){
    // increment
    countTimer1 += 65535;
}

// pin-change interrupt handler
ISR(INT0_vect){
    // read PORTD2:
    if (PIND & (1 << PORTD2)) {
        // rising edge:
        // start 16-bit timer
        // Divide by 1
        TCCR1B |= (1<<CS10);
        // set overflow interrupt flag
        TIMSK1 |= 1<<TOIE1;
    }
    else {
        // falling edge
        // stop timer
        TCCR1B &= ~(1<<CS10);
        // calculate time passed
        countTimer1 += TCNT1;
        // reset counter in timer0
        TCNT1 = 0;
        // set flag
        echoDone = 1;
    }
}

int main(){
    // HC-SR04
    initHCSR04();
    USART_Init();
    // set as output
    DDRB |= (1 << PORTB3);
    
    char str[16];
    char space[] = " .";
    float prevDist = 0.0;

    while (1) {
        float dist = getDistanceHCSR04();
        // sensor only works till 400 cm - if it exceeds, this value just send previous reading
        if (dist > 400 || dist < 2) dist = prevDist;
        
        sprintf(str, "%f\n", dist);
        USART_putstring(str);
        prevDist = dist;
        _delay_ms(70);
    }
    return 0;
}










/*int main(){
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
		_delay_ms(10000);
		for (idx = 0; idx < NUM_SENSOR; idx++){
		
		
		}
		//cur = sensors[0].pulse/58;
	}
	return 0;
}*/


