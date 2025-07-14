ENTRY(reset)
MEMORY{
	flash	: org = 0x08000000, len = 256k
	sram	: org = 0x20000000, len = 48k
}

stack_top = ORIGIN(sram) + LENGTH(sram); 

SECTIONS{
	.text : {
		KEEP(*(.text.ivt))
		*(.text*)
	} > flash

	.data : {
		*(.data*)
	} > sram AT > flash

	.bss : {
		*(.bss*)
	} > sram 
}
