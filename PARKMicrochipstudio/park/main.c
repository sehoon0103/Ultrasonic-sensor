#include "board.h"
#include "timer0.h"
#include "uart.h"
#include "tone.h"
#include "ultrasonic.h"
#include "switch.h"
#include "protocol.h"
#include <stdio.h>

extern volatile uint8_t time_update_flag;
extern volatile uint16_t time;

extern uint8_t g_slave_id;
extern uint8_t reg[256];

//======================================================
#define  DETECTION_TIME (3000) //ms
#define  DETECTION_HEIGHT (90) //cm

//======================================================

#define SW_SET_POSITION (0)

#include <avr/eeprom.h>
// EEPROM 내의 주소계산용 변수
uint16_t EEMEM ee_instal_position = 0;

// install position 저장(변경시에만 쓰기)
void save_position(uint16_t pos) {
	eeprom_update_word(&ee_instal_position, pos);
}

// install position 읽기
uint16_t read_position(void) {
	return eeprom_read_word(&ee_instal_position);
}

//=======================================================



uint8_t update_stable_state(uint8_t input_value) {
	static uint8_t current_state = 0;
	static uint8_t last_input = 0;
	static uint32_t last_change_time = 0;
	
	if (input_value != last_input)
	{
		last_change_time = millis();
		last_input = input_value;
	}
	else
	{
		if ((millis() - last_change_time) >= DETECTION_TIME && input_value != current_state) {
			current_state = input_value;
		}
	}
	
	return current_state;
}


int main(void)
{
	sei(); // 전역인트럽트 활성화
	
	board_init();
	uart_init(9600);
	//uart_print("start!\n");
	timer0_init();
	us_init();
    //===================================================
	uint16_t distance = 400;
	uint16_t install_pos = read_position();
	//초기값
	if(install_pos > 400 || install_pos < 180)
	{
		install_pos = 400;
		save_position(install_pos);
	}
	
	SWITCHES_INIT(SW_SET_POSITION, D, 7); //PD7 SW_SET_POSITION로 등록
	g_slave_id = DIP_SW; //  dip 8 ON
    //===================================================
		 
	uint8_t prev_trigger = millis();
	static char buffer[16];
	uint8_t buffer_index = 0;
	 
	while(1)
	{
		uint8_t ms = millis();
		if (ms - prev_trigger >=50)
		{
			prev_trigger = ms;
			us_trigger();
		}

		if (time_update_flag) // 요청확인
		{
			time_update_flag = 0;			
			distance = time * (0.0343 /2 * 278.3 / 262);	
			
			uint8_t parked = update_stable_state(install_pos - distance >= DETECTION_HEIGHT);
			reg[0x10] = parked; // reg 변수에 저장
			if (parked)
			{
				GREEN_LED_OFF();
				RED_LED_ON();
			}
			else
			{
				GREEN_LED_ON();
				RED_LED_OFF();
			}

		}
		
		
		
		 //===================================================
		 uint8_t switch_event = switches_update();
		 if (switch_event == SW_SET_POSITION);
		 {
			 install_pos = distance > 180 ? distance : 180;
			 save_position(install_pos);
		 }
		  //===================================================
		  
		  while (uart_is_available())
		  {
			  char c = uart_rx();
			  if (c == '$')
			  {
				  buffer_index = 0;
				  buffer[buffer_index++] = c;
		      }
			  else if (c == '\n')
			  {
				  
				  buffer[buffer_index++] = c;
				  buffer[buffer_index] = '\0';
				  slave_receive_and_respond(buffer);
				  buffer_index = 0;
			  }
			  else if (buffer_index > 0)
			  {
				  buffer[buffer_index++] = c;
				  if(buffer_index >= 16) // overflow
				      buffer_index = 0;
			  }
		  }
		  _delay_ms(1);
		
	}
}

