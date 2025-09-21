/* multiboot header - This must be at the start of the kernel */
typedef struct multiboot_header {
    unsigned long magic;
    unsigned long flags;
    unsigned long checksum;
} multiboot_header_t;

__attribute__((section(".multiboot"))) multiboot_header_t header = {
    0x1BADB002,        // Multiboot v1 magic
    0x00000003,        // Flags (align + memory info)
    -(0x1BADB002 + 0x00000003) // Checksum
};

#include"video.h"
#include"idt.h"
#include"mm.h"
#include"ramfs.h"
#include"sched.h"

// Prosty przykładowy task
static void task_logger(void* arg){
    (void)arg;
    print_string(".");
}

void _start() {
    clear_screen();
    print_string("Witam w systemie operacyjnym! Autorzy: Jan Pachla i Patryk Skrzypczak. System zawiera: bootloader, podstawowy task scheduler, memory manager\n");

    // IDT (klawiatura na IRQ1 ustawiana w idt.c)
    idt_install();

    // Inicjalizacja nowych modułów
    mm_init();
    ramfs_init();
    scheduler_init();

    // Demo RAMFS
    const char* msg = "Hello RAMFS!\n";
    int etc = ramfs_mkdir(0, "etc");
    (void)ramfs_create(etc, "motd.txt", msg, 13);

    // Demo task
    task_create("logger", 1, task_logger, 0);

    // Pętla główna — zamiast while(1) {} uruchamiamy scheduler
    while (1) {
        scheduler_run_once();
    }
}
