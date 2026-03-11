#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>
#include <stdint.h>

// 디바운스 시간(ms)
#define DEBOUNCE_TIME 50

//#define MAX_SWITCHES 4
#define MAX_SWITCHES 1


//스위치 초기화 매크로 (스위치 이름과 함께)
#define SWITCHES_INIT(switch_name, port_letter, pin_num) \
switch_init_internal(switch_name, &PIN##port_letter, &DDR##port_letter, &PORT##port_letter, 1)

//함수 선언
uint8_t switch_init_internal(uint8_t switch_index, volatile uint8_t* pin_reg,
volatile uint8_t* ddr_reg, volatile uint8_t* port_reg, uint8_t pin_mask);
uint8_t switches_update(void);
uint8_t switch_pressed(uint8_t switch_name);
uint8_t switch_released(uint8_t switch_name);

#endif // SWITCH_H
