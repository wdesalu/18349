/**
 *	adesalu, kafisher, lrbloch
 *	globals.h
 *	defines any global vars used in our program not provided to us
**/

#define POSITIVE_OFFSET		0x00800000	/* bit mask for positive offset bit */
#define LDR_PC_OPCODE		0xe51ff004	/* encoding for LDR pc, pc, #-4 */
#define SET_ICMR_M0_IRQ		0x04000000	/* bit in ICMR_ADDR that needs to be set for IRQs */
#define GOOD_INSTRUCTION	0xe41ff000	/* opcode for LDR pc, pc, #imm12 */
#define LDR_MASK		0xfe1ff000	/* bit mask for GOOD_INSTRUCTION */
#define BAD_CODE		0xbadc0de	/* bad code, spelled in hex */
#define SWI_PTR			0x08		/* addr of SWI ptr in uboot vector table */
#define IRQ_PTR			0x18		/* addr of IRQ ptr in uboot vector table */
#define UBOOT_SWI_PC		0x10		/* pc val when loading swi instruction in vector table */
#define UBOOT_IRQ_PC		0x20		/* pc when loading irq in vector table */
#define OFFSET_MASK		0xfff		/* masks out lower 12 bits to get offset */
#define FREQ_MS_FACTOR		100		/* number we must divide FREQ_VERDEX by to get ms */
#define TIME_INCR		10		/* increment in ms */
#define SDRAM_START		0xa0000000	/* where SDRAM begins */	
#define SDRAM_END		0xa3ffffff	/* where it ends */
#define SDRAM_SIZE		0x03ffffff	/* size of SDRAM */
