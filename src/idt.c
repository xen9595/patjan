#include "kernel.h"
#include "idt.h"
#include "types.h"

extern void idt_flush(uint32_t);      // z src/idt_flush.s
extern void keyboard_stub(void);      // z src/keyboard_stub.s

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}

void idt_install(void) {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // Wyczyść całą tablicę
    for (int i = 0; i < 256; i++) {
        idt_entries[i].base_lo = 0;
        idt_entries[i].base_hi = 0;
        idt_entries[i].sel     = 0x08;  // kernel code segment
        idt_entries[i].always0 = 0;
        idt_entries[i].flags   = 0x8E;  // present, ring 0, 32-bit interrupt gate
    }

    // IRQ1 (klawiatura) → handler w ASM
    idt_set_gate(33, (uint32_t)keyboard_stub, 0x08, 0x8E);

    // Załaduj IDT przez stub ASM
    idt_flush((uint32_t)&idt_ptr);
}
