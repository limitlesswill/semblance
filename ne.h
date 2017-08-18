#ifndef __NE_H
#define __NE_H

#include "semblance.h"

#ifdef USE_WARN
#define warn(...)       fprintf(stderr, "Warning: " __VA_ARGS__)
#else
#define warn(...)
#endif

#define DUMPHEADER      0x01
#define DUMPRSRC        0x02
#define DUMPEXPORT      0x04
#define DUMPIMPORTMOD   0x08
#define DISASSEMBLE     0x10
#define SPECFILE        0x80
word mode; /* what to dump */

#define DISASSEMBLE_ALL 0x01
#define DEMANGLE        0x02
word opts; /* additional options */


enum {
    GAS,
    NASM,
    MASM,
} asm_syntax;

extern const char *const rsrc_types[];
extern const size_t rsrc_types_count;

typedef struct _entry {
    byte flags;
    byte segment;
    word offset;
    char *name;     /* may be NULL */
} entry;

typedef struct _export {
    word ordinal;
    char *name;
} export;

typedef struct _import_module {
    char *name;
    export *exports;
    unsigned export_count;
} import_module;

/* per-file globals */
byte *import_name_table;
entry *entry_table;
unsigned entry_count;
import_module *import_module_table;

/* 66 + 67 + seg + lock/rep + 2 bytes opcode + modrm + sib + 4 bytes displacement + 4 bytes immediate */
#define MAX_INSTR       16

extern void print_rsrc(long start); /* in ne_resource.c */
extern void print_segments(word count, word align, word entry_cs, word entry_ip); /* in ne_segment.c */

#define MAXARGS		256

extern word disassemble_segment[MAXARGS];
extern word disassemble_count;

extern word resource_type[MAXARGS];
extern word resource_id[MAXARGS];
extern word resource_count;

#endif /* __NE_H */
