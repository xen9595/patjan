/* src/keyboard_stub.s  — IRQ1 (klawiatura) stub dla IDT */

    .section .text
    .globl  keyboard_stub
    .type   keyboard_stub, @function
keyboard_stub:
    /* CPU już wyłączył IF na wejściu do ISR */
    pushal              /* zachowaj ogólne rejestry */
    cld                 /* dla pewności: kierunek kopiowania w przód */

    call    keyboard_handler   /* C handler: czyta 0x60 i wysyła EOI (0x20) */

    popal               /* przywróć rejestry */
    iret                /* powrót z przerwania (32-bit, iretl) */
