#include "board.h"
#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h> // 인터럽트 서비스 루틴

#define USART_TX_BUFFER_SIZE 64
#define USART_RX_BUFFER_SIZE 64

// === RS-485 TR 제어 매크로===
#define RS485_TR_DDR   DDRC
#define RS485_TR_PORT  PORTC
#define RS485_TR_PIN   (7)

#define RS485_TR_TX()  (RS485_TR_PORT |=  (1 << RS485_TR_PIN)) // 송신 모드
#define RS485_TR_RX()  (RS485_TR_PORT &= ~(1 << RS485_TR_PIN)) // 수신 모드
 
// volatile : 최적화 금지 (무조건 읽어라)
// interrupt <--> main
// ring buffer
volatile uint8_t tx_buffer[ USART_TX_BUFFER_SIZE];
volatile uint8_t tx_head =0;
volatile uint8_t tx_tail =0;
volatile uint8_t rx_buffer[ USART_RX_BUFFER_SIZE];
volatile uint8_t rx_head =0;
volatile uint8_t rx_tail =0;

ISR(  USART_RX_vect ) // 수신 : 생산 : rx_head
{
	uint8_t data = UDR0; // 버퍼로 부터 데이터를 읽음
	uint8_t next = rx_head + 1; // 다음인덱스
	
	if (next >= USART_RX_BUFFER_SIZE) next = 0; //ring
	
	if (next  == rx_tail) // buffer full??
		return ; // 처리 안함
	
	rx_buffer[rx_head] = data;
	rx_head = next;
} 

ISR(  USART_UDRE_vect )// 송신버퍼 빌때 :  소비 : tx_tail
{
	if(tx_head == tx_tail) // blank buffer
	{
		UCSR0B &= ~(1 << UDRIE0);    //비활성화)
		UCSR0A |= (1 <<TXC0);        //TX Complete 플래그 클리어
		UCSR0B |= (1 << TXCIE0);     //TX Complete 인터럽트 활성화
		return;
	}
	
	UDR0 = tx_buffer[tx_tail];
	uint8_t next = tx_tail + 1; // 다음인덱스
	
	if (next >= USART_TX_BUFFER_SIZE) next = 0; //ring
	tx_tail = next;
}

// === 송신 완료 (TXC) 인터럽트 ===
ISR(USART_TX_vect)
{
	RS485_TR_RX();                  // 수신 모드 전환(TR LOW)
	UCSR0B &= ~(1 << TXCIE0);       // TX Complete 인터럽트 비활성화
}



void uart_init(uint32_t baud) // ~115200 :32
{
	//baud rate
	UBRR0 = (F_CPU / 16 / baud) - 1;
	
	// uart mode 설정 : 8-bit비동기 ,no parity  1 stop
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); 
	
	//송수신 및 수신 인터럽트 활성화
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	
	// RS485 TR핀 설정
	RS485_TR_DDR |= (1<<RS485_TR_PIN); //출력 모드
	RS485_TR_RX();                     //기본 수신 모드
	 
	// 인터럽트 활성화
	sei();	
} 

void uart_tx(uint8_t data) // non-block 함수 :생산 : tx_head
{
	uint8_t next = tx_head + 1; // 다음인덱스
	
	if (next >= USART_TX_BUFFER_SIZE) next = 0; //ring
	
	while (next  == tx_tail){} // buffer full??: 대기 ==>좀기다리면 자리가 나옴
	
	tx_buffer[tx_head] = data;
	tx_head = next;
	
	RS485_TR_TX();         // 송신 모드 전환(TR HIGH)
	UCSR0B |= (1<<UDRIE0); // 송신 버퍼 빔 인터럽트 활성화
}

uint8_t uart_rx() // non-block 함수 :소비 : rx_tail
{
	while(rx_head == rx_tail){} // blank buffer ==> 대기 : blocking
	
	uint8_t data = rx_buffer[rx_tail];
	uint8_t next = rx_tail + 1; // 다음인덱스
	
	if (next >= USART_RX_BUFFER_SIZE) next = 0; //ring
	rx_tail = next;
	return data;
}

uint8_t uart_is_available()
{
	return (rx_head != rx_tail);
}

void uart_print(const char *s )
{
	char c;
	// *s : s가 가리키는 대상(문자)
	for(;(c =*s) ;s++ ) // s++ 다음 문자로 가리키는 대상 이동
	{
		uart_tx(c); //송신
	}
}

void uart_test()
{
	uart_init(9600);
	
	while (1)
	{
		RED_LED_TOGGLE();
		uart_print("hello\n");
		_delay_ms(1000);

	}
	
}

