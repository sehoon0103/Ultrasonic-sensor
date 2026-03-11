#include "switch.h"


//비트 마스크 매크로
#define BIT_MASK(pin)               (1<<(pin))

//간단한 핀 제어 매크로
#define PIN_INPUT(port, pin)     DDR##port &= ~BIT_MASK(pin)
#define PIN_OUTPUT(port, pin)    DDR##port |= BIT_MASK(pin)
#define PIN_HIGH(port, pin)      PORT##port |= BIT_MASK(pin)
#define PIN_LOW(port, pin)       PORT##port &= ~BIT_MASK(pin)
#define PIN_READ(port, pin)      ((PIN##port & BIT_MASK(pin)) !=0)
#define PIN_PULLUP(port, pin)    do { PIN_INPUT(port, pin); PIN_HIGH(port, pin); } while(0)
	
// millis() 함수 선언 (외부에서 구현 필요)
extern uint32_t	millis(void);



// 스위치 구조체
typedef struct {
	volatile uint8_t* port;         //포트 레지스터(예: &PIND)
	uint8_t pin_mask;               //핀 마스크(예: 1<<6)
	uint32_t last_time;             //마지막 상태 변경 시간
	uint8_t last_state;             //이전 상태(0 또는 1)
	uint8_t current_state;          //현재 디바운스된 상태 (0 또는 1)
	uint8_t prev_debounced_state;   //이전 디바운스된 상태(press detection용)
	} switch_t;
	
	
	
// 스위치 배열과 개수 저장(static으로 내부 사용)
static switch_t switches[MAX_SWITCHES];   //최대 개수로 배열 선언
static uint8_t switch_count = 0;
	
// 내부 초기화 함수(지정된 인덱스에 등록)
uint8_t switch_init_internal(uint8_t switch_index, volatile uint8_t*pin_reg,
volatile uint8_t* ddr_reg, volatile uint8_t* port_reg, uint8_t pin_mask) {
	if (switch_index >= MAX_SWITCHES) return 255; // 실패 - 인덱스 범위 초과
	
	switch_t* sw = switches + switch_index;
	
	//핀을 입력으로 설정하고 풀업 활성화
	*ddr_reg &= ~pin_mask;  // 입력 설정
	*port_reg |= pin_mask;  // 풀업 활성화
	
	sw->port = pin_reg;
	sw->pin_mask = pin_mask;
	sw->last_time = 0;
	sw->last_state = (*sw->port & sw->pin_mask) ? 1 : 0;
	sw->current_state = sw->last_state;
	sw->prev_debounced_state = sw->current_state; // 초기화 추가
	
	
	// switch_count 업데이트 (가장 큰 인덱스+1로 설정)
	if (switch_index >= switch_count) {
		switch_count = switch_index + 1;
	}
	
	return switch_index;
}

//모든 스위치 상태 업데이트 및 방금 눌린 스위치 인덱스 리턴
//리턴값: 방금 눌린 스위치 인덱스(0~7), 없으면 255
uint8_t switches_update(void) {
	uint32_t now = millis();
	uint8_t pressed_switch = 255; // 기본값: 눌린 스위치 없음
	
	for (uint8_t i = 0; i< switch_count; i++) {
		switch_t* sw = switches + i;
		
		//초기화되지 않은 스위치는 건너뛰기
		if (sw->port == 0) continue;
		
		uint8_t raw_state = (*sw->port & sw->pin_mask) ? 1 : 0;
		
		//상태 변경 감지
		if (raw_state != sw->last_state) {
			sw->last_time = now;
			sw->last_state = raw_state;
		}
		
		//디바운스 시간 경과 후 상태 확정
		if ((now - sw ->last_time) > DEBOUNCE_TIME) {
		    // 이전 디바운스된 상태 저장
			sw->prev_debounced_state = sw->current_state;
			sw->current_state = raw_state;
			
			//방금 눌린 스위치 감지(HIGH->LOW 전환, active low)
			if (sw->prev_debounced_state == 1 && sw->current_state == 0) {
				pressed_switch = i; // 가장 먼저 발견된 눌린 스위치만 리턴
			}
		}
	}
	
	return pressed_switch;
}

//스위치 눌림 상태(LOW active) - 스위치 이름으로 접근
uint8_t switch_pressed(uint8_t switch_name) {
	if (switch_name >= MAX_SWITCHES) return 0; 
	if (switches[switch_name].port == 0) return 0; // 초기화되지 않은 스위치
	return !switches[switch_name].current_state;
}

// 스위치 놓임 상태 (HIGH) - 스위치 이름으로 접근
uint8_t switch_released(uint8_t switch_name) {
	if (switch_name >= MAX_SWITCHES) return 0;
	if (switches[switch_name].port == 0) return 0; // 초기화되지 않은 스위치
	return switches[switch_name].current_state;
}