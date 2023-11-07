#include "libUart.h"

static RXBuff_t *rxbuffer_p = NULL;

static void Uart_putc(uint8_t chData) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  //   while ((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = chData;
}

void uart_init(void) {
  UBRR0H = (uint16_t)(BAUD_PRESCALER >> 8);
  UBRR0L = (uint16_t)BAUD_PRESCALER;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_puts(uint8_t *s) {
  while (*s) {
    Uart_putc(*s);
    s++;
  }
}

void uart_set_rxBuffer(RXBuff_t *rxb) {
  if (rxb != NULL) {
    rxbuffer_p = rxb;
  }
}

ISR(USART_RX_vect) {
  if (rxbuffer_p == NULL) {
    return;
  }
  uint8_t c = UDR0;
  rxbuffer_p->buffer[rxbuffer_p->buffer_IDX] = c;

  if ((c == '\n') || (rxbuffer_p->buffer_IDX == UART_BUFFER_SIZE - 1)) {
    rxbuffer_p->linecomplete = 1;
  } else {
    rxbuffer_p->buffer_IDX++;
  }
}
