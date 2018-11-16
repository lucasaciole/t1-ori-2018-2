#ifndef _ORIT1_INDEX_H
#define _ORIT1_INDEX_H	1

#include "main.h"

typedef struct {
	unsigned int RRN;
	unsigned int key;
} i_primary_index;

typedef struct {
#ifndef DELIMITED
	char[20] name;
#else
	Sstr name;
#endif
	unsigned int ilist_index;
} i_name_index;

typedef struct {

} ilist_item;