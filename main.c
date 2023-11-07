#include "libUart.h"
#include <avr/io.h>

int main(void) {
  uart_init();
  RXBuff_t rxbuffer;
  uart_set_rxBuffer(&rxbuffer);

  while (1) {
    if (rxbuffer.linecomplete == 1) {
      uart_puts(rxbuffer.buffer);
      rxbuffer.linecomplete = 0;
      rxbuffer.buffer_IDX = 0;
    }
  }
}
