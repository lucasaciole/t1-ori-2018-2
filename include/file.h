#ifndef _ORIT1_FILE_H
#define _ORIT1_FILE_H	1

#include "main.h"

void insert(FILE *file, size_t qty, Entry *regs);
bool find_by_entry_number(unsigned int number, Entry *result, FILE *file, size_t *pos);
bool find_by_entry_key(unsigned int key, Entry *result, FILE *file, size_t *pos);
bool find_by_entry_key(unsigned int key, Entry *result, FILE *file, size_t *pos);
bool delete_entry(FILE *file, size_t pos, size_t size);

#endif // _ORIT1_FILE_H