# @file pack.mk
#
# @ Authors: Sara Roy <slroy@andrew.cmu.edu>
# @          Samantha Klonaris <sklonari@andrew.cmu.edu>
# @	      Derek Miller <damiller@andrew.cmu.edu>
# @ Date: 11/4/12

# Modified hello.c's makefile for rot13
PROGS_ROT13_OBJS := rot13.o
PROGS_ROT13_OBJS := $(PROGS_ROT13_OBJS:%=$(TDIR)/rot13/%)
ALL_OBJS += $(PROGS_ROT13_OBJS)

$(TDIR)/bin/rot13 : $(TSTART) $(PROGS_ROT13_OBJS) $(TLIBC)

