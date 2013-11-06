# adesalu
# lrbloch
# kafisher

CC = gcc
CFLAGS = -Wall -Werror

objects = math.o calc.o

default: calc

.PHONY: default clean clobber

calc: $(objects)
	$(CC) -o $@ $^

math.o: math.c math.h

calc.o: calc.c math.h 

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(objects)

clobber: clean
	rm -f calc
