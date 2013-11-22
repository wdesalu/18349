ARM_OBJS := reg.o psr.o S_Handler.o I_Handler.o read.o write.o sleep.o load_user_prog.o init_irq.o C_IRQ_Handler.o C_SWI_Handler.o

ARM_OBJS := $(ARM_OBJS:%=$(KDIR)/arm/%)

KOBJS += $(ARM_OBJS)
