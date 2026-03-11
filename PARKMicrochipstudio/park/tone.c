#include "board.h"
#include "tone.h"

// tone()을 위한 변수
static volatile uint8_t isToneActive = 0;

void tone(unsigned long frequency) 
{
	// 주파수 유효성 검사
	if (frequency == 0 || frequency > 10000) 
	{ // 상한값 추가
		tone_stop();
		return;
	}
	
	// PB1(OC1A) 핀을 출력으로 설정
	DDRB |= (1 << PB1);
	
	// 타이머 1 설정 - 정확한 CTC 모드
	TCCR1A = 0;                    // CTC 모드를 위해 COM1A1:0을 나중에 설정
	TCCR1B = (1 << WGM12);         // CTC 모드, OCR1A가 TOP 값
	
	// 클럭 선택 (분주율 설정)
	// 16MHz 시스템 클럭 가정, 분주율 8 => 2MHz 타이머 클럭
	TCCR1B |= (1 << CS11);         // 분주율 8
	
	// 주파수 계산: 2MHz / (2 * 주파수) - 1
	uint16_t ocr_val = (2000000 / (2 * frequency)) - 1;
	OCR1A = ocr_val;
	
	// 출력 핀 설정 - 비교 일치 시 토글
	TCCR1A |= (1 << COM1A0);
	
	// tone 활성화 상태 업데이트
	isToneActive = 1;
}

void tone_stop() 
{
	// 타이머 1의 출력 설정을 리셋
	TCCR1A = 0; // OC1A 핀에서 PWM 출력 중지
	TCCR1B = 0; // 타이머 1 비활성화
	isToneActive = 0; // 음을 멈춤
}

void tone_test() 
{
	while (1)
	{
		tone(440);
		_delay_ms(1000);
		tone_stop();
		_delay_ms(1000);

	}
}