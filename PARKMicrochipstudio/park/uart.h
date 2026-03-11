#ifndef UART_H_
#define UART_H_


void uart_init(uint32_t baud);
void uart_tx(uint8_t data);
uint8_t uart_rx();
uint8_t uart_is_available();
void uart_print(const char *s );
void uart_test();

#endif /* UART_H_ */