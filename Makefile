#############
# TOOLCHAIN #
#############

CC =		avr-gcc
LD =		avr-ld
STRIP =		avr-strip
OBJCOPY =	avr-objcopy
SIZE =		avr-size

######################
# TARGET AND SOURCES #
######################

TARGET =	hello
# --> where the main function is#
SOURCES =
# --> any other sources to include#

####################
# BUILD PARAMETERS #
####################

MCU =		atmega328
# --> tells avr-gcc which microcontroller we are using#
F_CPU =		16000000
# --> Clock speed in Hz#
BAUD =		9600
# --> baud rate for sending messages
CFLAGS =	-Wall -Werror -Os -DF_CPU=$(F_CPU) -I. -mmcu=$(MCU) \
		-DBAUD=$(BAUD)
#Wall --> Turn on all warnings#
#Werror --> All warnings are errors#
#0s --> optimize for space#
#I. --> looks for header files in the current directory#
#-mmcu --> tells the compiler which part to build for#
BINFORMAT =	ihex
# --> to build an Intel hex file to upload#

##########################
# PROGRAMMING PARAMETERS #
##########################

PROGRAMMER =	arduino
# --> using the arduino programmer
PART =		m328p
PORT =		$(shell ls /dev/ttyACM? | head -1)
# --> figuring out which port the arduino is connected to. Picks the first available one
AVRDUDE =	avrdude -v -p $(PART) -c $(PROGRAMMER) -P $(PORT)
AVRDUDE_FLASH =	-U flash:w:$(TARGET).hex
#--> write into flash space, where the program is stored


#building the program#

.PHONY: all
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O  $(BINFORMAT) -R .eeprom $(TARGET).elf $(TARGET).hex
	$(SIZE) -C --mcu=$(MCU) $(TARGET).elf

$(TARGET).elf: $(TARGET).c $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(TARGET).c
	$(STRIP) $(TARGET).elf

.PHONY: program
program: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLASH)

.PHONY: clean
clean:
	rm -f *.hex *.elf *.eeprom
