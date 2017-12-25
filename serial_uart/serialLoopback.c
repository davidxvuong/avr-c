#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

int main() {
	char serialChar;

	initUSART();
	printString("Hello World!\r\n");

	while(1) {
		serialChar = receiveByte();
		// transmitByte(serialChar);
		printByte(serialChar);
		printString("\r\n");
	}

	return 0;
}