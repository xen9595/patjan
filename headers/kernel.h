#ifndef KERNEL_H
#define KERNEL_h

#include"video.h"
#include"idt.h"
#include"types.h"
#include"io.h"


extern void clear_screen();
extern void print_string();
extern void protmodesetup();
extern void idt_install();
extern void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
extern void idt_flush(uint32_t);
extern void keyboard_handler();

extern idt_entry_t idt_entries[256];
extern idt_ptr_t idt_ptr;

#endif
