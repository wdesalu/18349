.global init_irq

init_irq:
	MSR	cpsr, #0x12		@ switch to IRQ mode
	MOV	sp, #0xa1000000;	@ set up stack
	MSR	cpsr, #0x13		@ back to SVC mode
