CC      = gcc
OBJCOPY = objcopy
CFLAGS  = -O2 -ffreestanding -Wall -Werror -nostdinc -g -I ../libc/include -I ./uboot/include
LDFLAGS = -nostdlib -Wl,-N,-Ttext,$(LOAD_ADDR) 

LOAD_ADDR = 0xa2000000

STUBS   = ../../part2/uboot/stubs.o
CRT0    = ../libc/crt0.o
LDLIBS  = ../libc/libc.a

objects = rot13.o

default: rot13.bin

.PHONY: default clean clobber

rot13.bin: rot13
	$(OBJCOPY) -O binary $< $@

rot13: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS) $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f rot13 $(objects)

clobber: clean
	rm -f rot13.bin
