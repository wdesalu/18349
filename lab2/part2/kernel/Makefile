CC	= gcc
OBJCOPY = objcopy
CFLAGS  = -O2 -ffixed-r8 -ffreestanding -Wall -Werror -nostdinc \
          -I ../uboot/include -I include
ASFLAGS = -nostdinc -I ../uboot/include -I include
LDFLAGS = -nostdlib -Wl,-N,-Ttext,$(LOAD_ADDR)

LOAD_ADDR = 0xa3000000

STUBS = ../uboot/stubs.o

objects = kernel.o

default: kernel.bin

.PHONY: default clean clobber

kernel.bin: kernel
	$(OBJCOPY) -O binary $< $@

kernel: start.o exit.o read.o write.o S_Handler.o load_user_prog.o C_SWI_Handler.o $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

end: end.o $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

load_user_prog: load_user_prog.o $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(ASFLAGS) -o $@ $<

clean:
	rm -f kernel start.o end.o read.o write.o S_Handler.o load_user_prog.o C_SWI_Handler.o $(objects)

clobber: clean
	rm -f kernel.bin
