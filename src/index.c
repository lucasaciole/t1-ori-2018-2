#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "file.h"

const char *_INDEXFNAME = "indice.bin";
const char *_SECINDEXFNAME = "indice_nome.bin";

bool create_primary_index(FILE *data_f) {
	// Abre o arquivo se já existir, cria se não
	FILE *file = fopen(_INDEXFNAME, "rb+");
	if(file == NULL)
		file = fopen(_INDEXFNAME, "w");
	if(file == NULL) {
		puts(ERR_FILE_NOT_FOUND);
		return false;
	}

	// Lê arquivo de dados para inserir no índice
	rewind(data_f);
	Entry **entry_list;
	Entry *entry;
}

bool create_name_index(FILE *data_f) {
	// Abre o arquivo se já existir, cria se não
	FILE *file = fopen(_SECINDEXFNAME, "rb+");
	if(file == NULL) 
		file = fopen(_SECINDEXFNAME, "w");
	if(file == NULL) {
		puts(ERR_FILE_NOT_FOUND);
		return false;
	}
}