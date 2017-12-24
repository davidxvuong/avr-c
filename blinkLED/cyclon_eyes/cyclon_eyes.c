#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 85
#define LED_PORT PORTB
#define LED_PIN PINB
#define LED_DDR DDRB

int main() {
	uint8_t i = 0;
	LED_DDR = 0x3f;

	while (1) {

		while ( i < 5) {
			LED_PORT = ~(1 << i);
			_delay_ms(DELAY_TIME);
			i++;
		}

		while (i > 0) {
			LED_PORT = ~(i << i);
			_delay_ms(DELAY_TIME);
			i--;
		}

	}

	return 0;
}