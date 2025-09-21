/* src/idt_flush.s — pomocnik do lidt */

    .section .text
    .globl  idt_flush
    .type   idt_flush, @function
idt_flush:
    mov     4(%esp), %eax     /* arg: pointer do idt_ptr */
    lidt    (%eax)
    ret
