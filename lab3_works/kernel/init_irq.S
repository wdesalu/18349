.global init_irq

init_irq:
	MSR	cpsr, #0x12
	MOV	sp, #0xa1000000;
	MSR	cpsr, #0x13
