PROGS_EQUAL_OBJS := equal.o
PROGS_EQUAL_OBJS := $(PROGS_EQUAL_OBJS:%=$(TDIR)/equal/%)
ALL_OBJS += $(PROGS_EQUAL_OBJS)

$(TDIR)/bin/equal : $(TSTART) $(PROGS_EQUAL_OBJS) $(TLIBC)

