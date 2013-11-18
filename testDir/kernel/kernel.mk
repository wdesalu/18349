# @file kernel.mk
#
# @ Authors: Sara Roy <slroy@andrew.cmu.edu>
# @          Samantha Klonaris <sklonari@andrew.cmu.edu>
# @	      Derek Miller <damiller@andrew.cmu.edu>
# @ Date: 11/4/12

KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o

# Added swi_handler object
SWIDIR = $(TLIBCDIR)/swi/swi_handler.o

# Added sys_handler, irq_handler, setup_program objects
KOBJS := assert.o main.o raise.o sys_handler.o irq_handler.o setup_program.o
KOBJS := $(KOBJS:%=$(KDIR)/%)

ALL_OBJS += $(KOBJS) $(KSTART) $(SWIDIR)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS) $(SWIDIR)
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)
