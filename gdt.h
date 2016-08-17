#ifndef _GDT_H_
#define _GDT_H_ 1

#include <stdint.h>
#include "stdio.h"
#include "mem.h"

class gdt
{
public:
    gdt();
    ~gdt();
private:    
    /* Our GDT, with 3 entries, and finally our special GDT pointer */
    void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
};

#endif
