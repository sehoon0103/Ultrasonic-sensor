#ifndef BOARD_H_
#define BOARD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // 인터럽트 서비스 루틴

#define H(b)		(1<<(b))

#define BIT_TEST(r,b) (r & H(b))
#define SET_BIT(r,b)  r|= H(b)
#define CLEAR_BIT(r,b)  r&=~H(b)
#define TOGGLE_BIT(r,b)  r^=H(b)

//#define SW1				BIT_TEST(PIND,7)
#define DIP_SW          ((~PINC) & 0b11111)

#define RED_LED_ON()	CLEAR_BIT(PORTD,5)
#define RED_LED_OFF()	SET_BIT(PORTD,5)
#define RED_LED_TOGGLE() TOGGLE_BIT(PORTD,5)

#define GREEN_LED_ON()	CLEAR_BIT(PORTD,6)
#define GREEN_LED_OFF()	SET_BIT(PORTD,6)
#define GREEN_LED_TOGGLE() TOGGLE_BIT(PORTD,5)


void board_init();
void led_test();


#endif /* BOARD_H_ */