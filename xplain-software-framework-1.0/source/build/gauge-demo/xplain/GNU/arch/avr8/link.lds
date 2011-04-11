OUTPUT_FORMAT("elf32-avr", "elf32-avr", "elf32-avr")
OUTPUT_ARCH(avr:107)
ENTRY(_start)
SECTIONS
{
 . = 0;
 .text : {
  _text = .;
  *(.vectors)
  *(.avr.text.avr_runtime_init)
  *(.text.intc_priv_unhandled_irq)
  *(.text)
  *(.text.*)
  *(.progmem.gcc_sw_table)
  *(.progmem.data)
  . = ALIGN(2);
  _etext = .;
 }
 . = 0x800000 | 0x2000;
 .data : AT(LOADADDR(.text) + SIZEOF(.text)) {
  _data = .;
  *(.rodata)
  *(.rodata.*)
  *(.data)
  *(.data.*)
  . = ALIGN(2);
  _edata = .;
 }
 .bss (NOLOAD) : AT(LOADADDR(.data) + SIZEOF(.data)) {
  *(.bss)
  *(.bss.*)
  *(COMMON)
  . = ALIGN(2);
  _end = .;
 }
 .heap (NOLOAD) : {
  heap_area = .;
 }
 . = 0x800000 + 0x2000 + 0x2000 - 0x100 - 0x80;
 .stack (NOLOAD) : {
  stack_area = .;
  . = . + 0x100 + 0x80;
  . = ALIGN(2);
  _estack = .;
 }
}
