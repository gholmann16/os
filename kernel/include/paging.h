#include <types.h>

typedef struct Page
{
   u64_t present    : 1;   // Page present in memory
   u64_t rw         : 1;   // 0 = read only, 1 = writable
   u64_t user       : 1;   // 0 = kernel mode (ring 0-2), 1 = usermode (ring 0-3)
   u64_t pwt        : 1;   // policy write through: 1 = write to ram as well (not just cache)
   u64_t pcd        : 1;   // police cache disable: 1 = write to memory INSTEAD
   u64_t accessed   : 1;   // Has the page been accessed since last refresh?
   u64_t dirty      : 1;   // Has the page been written to since last refresh?
   u64_t pat        : 1;   // extra police bit, not used in practice
   u64_t global     : 1;   // not sure
   u64_t available  : 3;   // Extra unused bits
   u64_t address    : 40;  // middle 40 bits of physical address
   u64_t available2 : 7;   // Extra unused bits
   u64_t protection : 4;   // Assigns the page 1 of 16 keys
   u64_t nx         : 1;   // 0 = executable, 1 = non executable
} page_t;


void * kmalloc(u64_t sz, bool align, u64_t * physical);
page_t * get_page(u64_t addr, bool create);
