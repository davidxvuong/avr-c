#include <avr/io.h>
#include <util/delay.h>
#include "speaker_pins.h"
#include "scale16.h"
#include "USART.h"
#include "organ.h"


#define NOTE_LEN 0xf000

int main() {
	SPEAKER_DDR = (1 << SPEAKER);
	initUSART();

	printString("Serial Organ\r\n");

	char serial_input;
	uint16_t currentNoteLength = NOTE_LEN / 2;
	const uint8_t keys[] = { 'a', 'w', 's', 'e', 'd', 'f', 't',
		'g', 'y', 'h', 'j', 'i', 'k', 'o',
		'l', 'p', ';', '\''
	};
	const uint16_t notes[] = { G4, Gx4, A4, Ax4, B4, C5, Cx5,
		D5, Dx5, E5, F5, Fx5, G5, Gx5,
		A5, Ax5, B5, C6
	};

	uint8_t isNote;
	uint8_t i;

	while(1) {
		serial_input = receiveByte();
		transmitByte('N');

		isNote = 0;

		for (i = 0; i < sizeof(keys); i++) {
			if (serial_input == keys[i]) {
				play_note(notes[i], currentNoteLength);
				isNote = 1;
				break;
			}

		}

		if (!isNote) {
			if (serial_input == '[') {
				currentNoteLength = NOTE_LEN / 2;
			}
			else if (serial_input == ']') {
				currentNoteLength = NOTE_LEN;
			}
			else {
				rest(currentNoteLength);
			}
		}

		printString("Done\r\n");
	}

	return 0;
}