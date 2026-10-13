# ENG

# patjan OS

A simple educational operating system (32-bit kernel, C + assembly) featuring:
- A simple memory manager (bump allocator),
- RAM-FS (a simple in-memory file system),
- A task scheduler (cooperative or PIT-interrupt-driven),
- Interrupt handling (IDT, keyboard, PIT),
- Booting via Multiboot v1 + GRUB.

# Requirements

*On Ubuntu/Debian:*

sudo apt update
sudo apt install build-essential qemu-system-x86 grub-pc-bin xorriso mtools


*On Arch/Manjaro:*

sudo pacman -S base-devel qemu grub xorriso mtools


# Running

1. make clean
2. make
3. make run

The system should now boot successfully.


# PL

# patjan OS

Prosty system operacyjny w stylu edukacyjnym (kernel 32-bit, C + asm), zawierający:
- prosty memory manager (bump allocator),
- RAM-FS (prosty system plików w pamięci),
- task scheduler (kooperacyjny lub z przerwaniami od PIT),
- obsługę przerwań (IDT, klawiatura, PIT),
- boot przez Multiboot v1 + GRUB.

# Wymagania

*Na Ubuntu/Debian:*

sudo apt update
sudo apt install build-essential qemu-system-x86 grub-pc-bin xorriso mtools

*Na Arch/Manjaro*

sudo pacman -S base-devel qemu grub xorriso mtools

# Uruchamianie

1. make clean
2. make
3. make run

Teraz system powinien sie odpalic
