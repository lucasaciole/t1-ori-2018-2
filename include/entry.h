#ifndef _ORIT1_ENRY_H
#define _ORIT1_ENRY_H	1

#include "main.h"

bool read_entry(FILE *file, Entry *dst);
size_t write_entry(FILE *file, Entry *src);
void print_entry(Entry *entry);

#endif // _ORIT1_ENRY_H