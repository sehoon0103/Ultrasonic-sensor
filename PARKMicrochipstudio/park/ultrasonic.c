#include "board.h"
#include "timer0.h"

#define TRIGGER_HIGH()	SET_BIT(PORTD,3)
#define TRIGGER_LOW()	CLEAR_BIT(PORTD,3)
#define ECHO			BIT_TEST(PIND,2)


void us_trigger()
{
	TRIGGER_HIGH();
	_delay_us(10);
	TRIGGER_LOW();
}

volatile uint16_t time =0;
volatile uint8_t time_update_flag =0;
uint32_t start_time = 0;

ISR(INT0_vect)
{
	uint32_t us = micros();
	if (ECHO)
	{  // rising edge
		start_time = us;
	}
	else
	{ // falling edge
		time= us - start_time  ;
		time_update_flag = 1;
	}
}
void us_init()
{
	DDRD |= (1<<3); // trigger => out
	DDRD &= ~(1<<2); // echo => in / int0
	
	// echo pin : ext int0
	EICRA |=  (1<<ISC00); // mode:logical change
	EICRA &=  ~(1<<ISC01);
	EIMSK |=  (1<<INT0); // enable ext int0
	sei();
}
/*
void us_test()
{
	uart_init(9600);
	us_init();
	timer0_init();
	
	sei(); // 전역인터럽트 활성화
	
	us_trigger(); //첫 측정
	while(1)
	{
		if (time_update_flag) // 요청확인
		{
			time_update_flag = 0;
			us_trigger(); // 측정시작
			uint16_t d = time * (0.0343 /2 * 278.3 / 262);
			char s[8]; // buffer for string
			sprintf( s, "%d\n" ,d  );
			uart_print(s);
		}
		_delay_ms(1);
		
	}
}
*/