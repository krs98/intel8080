#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include "types.h"

struct Registers {
    union {
        u16 bc;
        struct {
            u8 c;
            u8 b;
        };
    };

    union {
        u16 de;
        struct {
            u8 e;
            u8 d;
        };
    };

    union {
        u16 hl;
        struct {
            u8 l;
            u8 h;
        };
    };

    u8 a;
};

struct Flags {
    u8 zero      : 1;
    u8 sign      : 1;
    u8 parity    : 1;
    u8 carry     : 1;
    u8 aux_carry : 1;
    u8 pad       : 3;
};

struct CPU {
    Registers regs;
    Flags flags;

    union {
        u16 sp;
        struct {
            u8 sp_low;
            u8 sp_hi;
        };
    };

    union {
        u16 pc;
        struct {
            u8 pc_low;
            u8 pc_hi;
        };
    };

    bool interrupts_enabled;

    u8 *memory;

    void (*in)(CPU *cpu); 
    void (*out)(CPU *cpu, u8 port);
};

void cpu_init(CPU *cpu, void (*in)(CPU *cpu), void (*out)(CPU *cpu, u8 port));
void cpu_reset(CPU *cpu);
void cpu_execute(CPU *cpu, u8 opcode);

u8 memory_read(CPU *cpu, u16 addr);
void memory_write(CPU *cpu, u16 addr, u8 value);

#endif
