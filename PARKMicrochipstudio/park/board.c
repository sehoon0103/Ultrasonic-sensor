#include "board.h"
// SWITCH 
#define TRIGGER_HIGH()	SET_BIT(PORTD,3)
#define TRIGGER_LOW()	CLEAR_BIT(PORTD,3)
#define ECHO			BIT_TEST(PIND,2)


void board_init()
{
	
	DDRD = (1<<5)| (1<<6);	// LED	
	RED_LED_OFF();
	GREEN_LED_OFF();
	DDRB = (1<<2);			// BUZZER
	
	DDRC = (1<<7);			// 485 
	PORTC |= 0b11111;		// DIP SWITCH : INTERNAL PULLUP INPUT
}


void led_test()
{
	while (1)
	{
		RED_LED_ON();
		GREEN_LED_ON();
		_delay_ms(500);
	
		RED_LED_OFF();
		GREEN_LED_OFF();
		_delay_ms(500);
	}
}
