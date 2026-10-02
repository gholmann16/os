CCFLAGS = -Iinclude -ggdb -c -ffreestanding

C_OBJS   = $(patsubst %.c,%.o,$(wildcard *.c))
ASM_OBJS = $(patsubst %.asm,%.o,$(filter-out entry.asm,$(wildcard *.asm)))

../kernel.bin: entry.o $(C_OBJS) $(ASM_OBJS)
	ld.lld -o $@ -Ttext 0xffff $^ --oformat binary

%.o: %.c
	gcc $< $(CCFLAGS) -o $@

%.o: %.asm
	nasm $< -f elf64 -o $@

clean:
	rm -f *.o ../kernel.bin
