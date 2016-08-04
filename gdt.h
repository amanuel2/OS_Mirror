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
    void gdt_set_gate(uint32_t index, uint64_t base, uint64_t limit,
                         bool descriptor_type, uint8_t descriptor_privilege,
                         bool bit64, bool granularity, bool op_size,
                         uint8_t segment_type);
};

#endif
