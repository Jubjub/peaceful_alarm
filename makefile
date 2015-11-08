CC = avr-gcc
LIBS = -lglfw
CFLAGS = -Wall -Os
UC = attiny13
PORT = com5

FUSES = -U lfuse:w:0x7a:m -U hfuse:w:0xff:m
CLOCK = 9600000
SRC = $(wildcard src/*.c) src/wavetables.h
OBJ = $(SRC:.c=.o)

out.hex: out.elf
	avr-objcopy -j .text -j .data -O ihex out.elf out.hex

program: out.hex
	avrdude -p $(UC) -c stk500v1 -P $(PORT) -b 19200 -q -U flash:w:out.hex

fuses:
	avrdude -p attiny13 -P com5 -c stk500v1  -b 19200 -q $(FUSES)

.c.o:
	$(CC) $(CFLAGS) $(OPTIMIZATION) -DF_CPU=$(CLOCK) -mmcu=$(UC) $< -c -o $@

out.elf: $(OBJ)
	$(CC) -DF_CPU=$(CLOCK) -Wall -Os -mmcu=$(UC) -o out.elf $(OBJ)
	avr-size out.elf

src/wavetables.h: tools/wavetables.py
	python tools/wavetables.py > src/wavetables.h

clean :
	$(RM) out.elf
	$(RM) out.hex
	$(RM) tools/*.pyc
	$(RM) src/wavetables.h
	$(RM) src/*.o

