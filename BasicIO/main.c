/*
 * Test Task 1.c
 *
 * Created: 01-Nov-19 10:29:52 AM
 * Author : Deborah Curtis
 */ 
#define F_CPU 16000000UL					//defines the frequency of the CPU

//include standard libraries
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

//include user libraries
#include "i2cmaster.h" 
#include "usart.h"							//to output to realterm or sdu terminal 

void turn_right(void);
void turn_left(void);
void go(void);
void reverse(void);
void stop(void);
void steppermotor(int);


int main(void)
{
	//configuring buttons
	DDRB = 0xFF;							//configure port b as output port
	PORTB = 0x00;							//output 0 on port b
	DDRD = 0xFF;							//configure port b as output port
	PORTD = 0x00;							//output 0 on port b
	
	i2c_init();								//initialize the communication for I2C
	uart_init();
	io_redirect();
	
	go;										//starts motor goes straight
	_delay_ms(10000);						//motor run time (10 sec)
	stop;									//stop motor
	
	turn_right;								//turns front wheel to the right
	
	go;										//starts motor - goes right
	_delay_ms(3000);						//motor run time (3 sec)
	stop;									//stops motor
	
	turn_left;								//turns front wheel straight
	
	go;										//starts motor - goes straight
	_delay_ms(10000);						//motor run time (10 sec)
	stop;									//stop motor
	
	turn_left;								//turns front wheel left
	
	go;										//starts motor - goes left
	_delay_ms(3000);						//motor run time (3 sec)
	stop;									//stop motor
	
	turn_right;								//turns front wheel straight
	
	go;										//starts motor - goes straight
	_delay_ms(10000);						//motor run time (10 sec)
	stop;									//stop motor
	
	reverse;								//motor reverses
	_delay_ms(10000);						//motor run time (10 sec)
	stop;									//stop motor
	
	return 0;
}

void go (void){
	PORTD=PORTD|0b00001000;			//sets pwm output pin to 1
	PORTD=PORTD|0b00000100;			//sets pin d4 to 1
	PORTD=PORTD&0b11101111;			//sets pin d1 to 0
}

void reverse (void){
	PORTD=PORTD|0b00001000;			//sets pwm output pin to 1
	PORTD=PORTD|0b00010000;			//sets pin d4 to 1
	PORTD=PORTD&0b11111011;			//sets pin d1 to 0
}

void stop (void){
	PORTD=PORTD&0b11110111;			//sets pwm output pin to 0
}

void turn_right (void){
	PORTB=0b00000011;				//AIN1, BIN1 high
	steppermotor(150);				//starts pwm to stepper motor
	PORTB=0b00010000;				//h-bridge standby
}

void turn_left (void){
	PORTB=0b00001100;				//AIN2, BIN2 high
	steppermotor(150);				//starts pwm to stepper motor
	PORTB=0b00010000;				//h-bridge standby
}

void steppermotor(int time){
	PORTD=PORTD&0b10011111;			//sets pins d5 & d6 to 0
	for (int i=0; i<time; i++){		//for loop will repeat 'time' times
		PORTD=PORTD|0b01000000;		//sets pin d6 to 1
		_delay_us(1);
		PORTD=PORTD|0b01100000;
		_delay_us(1);
		PORTD=PORTD&0b10111111;
		PORTD=PORTD|0b00100000;
		_delay_us(1);
		PORTD=PORTD|0b01100000;
		_delay_us(1);
	}
	PORTD=PORTD&0b10011111;
}