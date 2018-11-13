#ifndef _ORIT1_MAIN_H
#define _ORIT1_MAIN_H	1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Macros Constantes
#define V_DEPLOY 0
#define V_DEBUG 1
#define V_NOOBINGAROUND 2

// Configurações
#define FIXED_SIZE 1
#define VERBOSE_LEVEL V_NOOBINGAROUND

// Para segurar o Texto
#if FIXED_SIZE == 1
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
#if FIXED_SIZE == 1
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
	size_t next;
} Removed;

// Variaveis globais
const char *_FNAME;
const char *ERR_FILE_NOT_FOUND;
bool quiet;

// Ajudante (:D)
#if VERBOSE_LEVEL >= V_NOOBINGAROUND
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dprintf(...) // REJECTED
#endif

#endif