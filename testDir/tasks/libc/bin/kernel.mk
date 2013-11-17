KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o
SWIDIR = $(TLIBCDIR)/swi/swi_handler.o
BINDIR = $(TLIBCDIR)/bin

# All core kernel objects go here.  Add objects here if you need to.
KOBJS := assert.o main.o raise.o sys_handler.o
KOBJS := $(KOBJS:%=$(KDIR)/%)
ALL_OBJS += $(KOBJS) $(KSTART) $(SWIDIR) $(SYSDIR)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS) $(SWIDIR) $(SYSDIR)
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)
	@mv kernel $(BINDIR)
	@mv kernel.bin $(BINDIR)

