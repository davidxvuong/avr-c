#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "USART.h"

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_YELLOW PB3
#define LED_RED PB4
#define LED_GREEN PB5

#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD
#define BUTTON PD2

ISR(INT0_vect) {
	printString("Interrupt!\r\n");
	if (!bit_is_set(BUTTON_PIN, BUTTON)) {
		LED_PORT |= (1 << LED_YELLOW);
	}
	else {
		LED_PORT &= ~(1 << LED_YELLOW);
	}
}

void init_led_interrupt() {
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00);
	sei();
}

int main() {
	initUSART();
	LED_DDR |= ((1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_YELLOW));

	BUTTON_PORT |= (1 << BUTTON);

	init_led_interrupt();

	LED_PORT = (1 << LED_GREEN) | (0 << LED_RED);

	while(1) {
		_delay_ms(1000);
		LED_PORT ^= (1 << LED_GREEN) | (1 << LED_RED);
		_delay_ms(1000);
	}

	return 0;
}