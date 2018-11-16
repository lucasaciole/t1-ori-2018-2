#ifndef _ORIT1_MAIN_H
#define _ORIT1_MAIN_H	1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Para segurar o Texto
#ifndef DELIMITED
typedef char* Sstr;
#else
typedef struct {
	size_t length;
	char *data;
} Sstr;
#endif

// Registro
typedef struct {
	bool removed;
	unsigned int key;
#ifndef DELIMITED
	char lastname[20];
	char firstname[20];
	char address[40];
	char city[20];
	char uf[3];
	char zip[11];
	char phone[15];
#else
	Sstr lastname;
	Sstr firstname;
	Sstr address;
	Sstr city;
	Sstr uf;
	Sstr zip;
	Sstr phone;
#endif
} Entry;

typedef struct {
	bool removed;
	size_t size;
} Removed;

// Variaveis globais
const char *_FNAME;
const char *ERR_FILE_NOT_FOUND;
bool quiet;

// Ajudante (:D)
#ifdef VERBOSE_NOOBS
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dprintf(...) // REJECTED
#endif

#endif