#ifndef _ORIT1_ENRY_H
#define _ORIT1_ENRY_H	1

#include "main.h"

bool read_entry(FILE *file, Entry *dst);
void write_entry(FILE *file, Entry *src, bool reuse);
void print_entry(Entry *entry);

#endif // _ORIT1_ENRY_H