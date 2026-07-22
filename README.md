# GabrielOS

A hobby x86-64 operating system built from scratch in x86 assembly and C — no bootloader libraries or libc. Used [Nick Blundell's operating systems tutorial](https://angom.myweb.cs.uwindsor.ca/teaching/cs330/WritingOS.pdf) as a learning resource, with parts implemented and extended independently along the way.

## Features

- **Custom bootloader** (16-bit real mode) — loads the kernel from disk and prints a boot banner
- **Protected mode transition** — GDT setup and the jump from 16-bit real mode to 32-bit protected mode
- **Long mode transition** — page table identity mapping and the jump from 32-bit protected mode to 64-bit long mode
- **Interrupt Descriptor Table** — all 32 CPU exception vectors, plus the 8259 PIC remapped and wired up for all 16 hardware IRQs
- **Programmable Interval Timer** — IRQ0-driven timer with a configurable frequency and tick counter
- **VGA text-mode driver** — screen clearing, cursor hiding, string and hex output
- **Freestanding C kernel** — compiled with `-ffreestanding` and linked into a flat binary with `ld.lld`

## Getting Started

### Dependencies

- [NASM](https://www.nasm.us/)
- GCC
- `ld.lld` (LLVM linker, don't use the standard one)
- [QEMU](https://www.qemu.org/) (`qemu-system-x86_64`)

### Build & Run

```sh
./compile.sh   # assembles the bootloader, builds the kernel, and stitches together os.img
./run.sh       # boots os.img in QEMU
```

## Project Structure

```
boot/                16-bit bootloader, real mode -> protected mode -> long mode
  real_mode/         disk loading, printing, protected-mode entry, GDT
  protected_mode/    long mode page tables, GDT, long-mode entry
kernel/              kernel written in C
  include/           kernel headers
```

## Roadmap

- Paging and dynamic memory allocation
- User mode / syscalls
- Filesystem support
- Process scheduling

## Acknowledgments

Built while following Nick Blundell's operating systems tutorial as a learning resource.
