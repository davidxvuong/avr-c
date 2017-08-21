//https://kyleisom.net/projects/embedded-intro/getting-started/

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB5

static void init_UART(void) {
	//initialize baud rate
	UBRR0H = UBRRH_VALUE;	//UBRRH_VALUE is from the setbaud.h header file
	UBRR0L = UBRRL_VALUE;	//UBRRL_VALUE is from the setbaud.h header file

	//disable 2x transmission speed
	UCSR0A &= ~(1 << U2X0);

	//enable transmitter and receiver on 0
	UCSR0B = ((1 << TXEN0) | (1 << RXEN0));

	//Set up the frame of the data: 8 data bits, 1 stop bit
	UCSR0C = ((1 << UCSZ01) | (1 << UCSZ00));
}

static void newline(void) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 ='\r';

	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = '\n';
}

static void write_string(char *s) {
	int i = 0;

	while (s[i] != 0) {
		//wait until data register is empty
		loop_until_bit_is_set(UCSR0A, UDRE0);

		//send byte
		UDR0 = s[i];
		i++;
	}
}

int main (void) {
	LED_DDR |= _BV(LED_PIN);

	init_UART();

	write_string("Boot ok. DV");
	newline();

	while(1) {
		LED_PORT ^= _BV(LED_PIN);

		_delay_ms(1000);
	}

	return 0;
}
