#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

#define BOSS_DDR DDRD
#define BOSS_PORT PORTD
#define BOSS_PIN PIND
#define BOSS_BUTTON PD2

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB0

int main() {
	//initialization
	initUSART();
	LED_DDR |= (1 << LED_PIN);
	BOSS_DDR |= ~(1 << BOSS_BUTTON);
	BOSS_PORT |= (1 << BOSS_BUTTON);

	printString("Ready\r\n");
	transmitByte('O');

	while(1) {
		if (bit_is_clear(BOSS_PIN, BOSS_BUTTON)) {
			LED_PORT |= (1 << LED_PIN);
			printString("LED on \r\n");
			transmitByte('X');
		}
		else {
			LED_PORT &= ~(1 << LED_PIN);
		}
	}

	return 0;
}