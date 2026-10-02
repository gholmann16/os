#include <types.h>
#include <paging.h>
#include <string.h>
#define PAGE_SIZE 4096

void * kmalloc(u64_t sz, bool align, u64_t * physical) {
    // right above vga / bios rom stuff, 1MB, inside 2 MB map
    // physical address, un-dereferenceable
    static u64_t placement_address = 0x100000;
    // If the address is not already page-aligned
    if (align && placement_address & (u64_t)0xFFF) {
        placement_address &= ~(u64_t)0xFFF;
        placement_address += PAGE_SIZE;
    }
    if (physical) {
        *physical = placement_address;
    }
    void * result = (void *)placement_address;
    placement_address += sz;
    return result;
}

#define PML4 39     // Page Map Level 4 bits: 47-39
#define PDPT 30     // Page Directory Pointer Table: 38-30
#define PD 21       // Page Directory: 29-21
#define PT 12       // Page Table: 20-12

#define LAST_9 0x1FF

page_t * get_page(u64_t addr, bool create) {
    page_t * level = (page_t *)0x1000;
    int shifts[3] = {PML4, PDPT, PD};
    for (int i = 0; i < 3; i++) {
        page_t * current_map = &level[(addr >> shifts[i]) & LAST_9];
        if (!current_map->present) {
            if (!create) return 0;
            u64_t phys;
            page_t * virt = (page_t *)kmalloc(PAGE_SIZE, 1, &phys);
            memset(virt, 0, PAGE_SIZE);
            *current_map = (page_t){
                .address = phys >> PT,
                .present = true,
                .rw = true,
            };
        }
        // only works because it's a direct mapping below 2 MB
        // sign extension unnecessary since numbers are so low
        level = (page_t*)((u64_t)current_map->address << PT);
    }
    // caller handles if page entry exists or not
    return &level[(addr >> PT) & LAST_9];
}
