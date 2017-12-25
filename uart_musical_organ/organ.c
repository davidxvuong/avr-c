#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "speaker_pins.h"

void play_note(uint16_t period, uint16_t duration) {
	uint16_t elapsed;

	uint16_t i;

	for (elapsed = 0; elapsed < duration; elapsed++) {

		for (i = 0; i < period; i++) {
			_delay_us(1);
		}

		SPEAKER_PORT ^= (1 << SPEAKER);
	}
}

void rest(uint16_t duration) {
	do {
		_delay_us(1);
	} while (--duration);
}