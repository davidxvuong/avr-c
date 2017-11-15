#include <avr/io.h>
#include <util/delay.h>

void pov_display(uint8_t val) {
	PORTB = val;
	_delay_ms(2);
}

int main() {
	// uint8_t i;
	//Initialization
	DDRB = 0xff;	//Configure data register b, pin 0 to 5 as output pins

	//display pov data

	while(1) {
		// for (i = 0; i < 0b01000000; i++) {
		// 	pov_display(i);
		// }

		pov_display(0b00001110);
		pov_display(0b00011000);
		pov_display(0b10111101);
		pov_display(0b01110110);
		pov_display(0b00111100);
		pov_display(0b00111100);
		pov_display(0b00111100);
		pov_display(0b01110110);
		pov_display(0b10111101);
		pov_display(0b00011000);
		pov_display(0b00001110);

		PORTB = 0;
		_delay_ms(10);
	}

	return 0;
}