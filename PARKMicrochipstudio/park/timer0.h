#ifndef TIMER0_H_
#define TIMER0_H_


// Timer0 초기화 함수
void timer0_init(void);

// 밀리초 반환 함수
uint32_t millis(void);

// 마이크로초 반환 함수
uint32_t micros(void);

// 딜레이 함수 (밀리초)
void delay(uint32_t ms);

#endif /* TIMER_H_ */