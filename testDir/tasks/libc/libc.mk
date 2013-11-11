# @file libc.mk
#
# @ Authors: Sara Roy <slroy@andrew.cmu.edu>
# @          Samantha Klonaris <sklonari@andrew.cmu.edu>
# @	      Derek Miller <damiller@andrew.cmu.edu>
# @ Date: 11/4/12

TLIBC = $(TLIBCDIR)/libc.a
TSTART = $(TLIBCDIR)/crt0.o

# Added sys_handler object
SYSDIR = $(KDIR)/sys_handler.o

TLIBC_GLOBAL_OBJS := raise.o
TLIBC_GLOBAL_OBJS := $(TLIBC_GLOBAL_OBJS:%=$(TLIBCDIR)/%)

TLIBC_LIBS = swi string stdio stdlib
TLIBC_MKS = $(TLIBC_LIBS:%=$(TLIBCDIR)/%/libc.mk)

include $(TLIBC_MKS)

TLIBC_OBJS += $(TLIBC_GLOBAL_OBJS)
ALL_OBJS += $(TLIBC_OBJS) $(TSTART) $(SYSDIR)
ALL_CLEANS += $(TLIBC)

$(TLIBC) : $(TLIBC_OBJS)

