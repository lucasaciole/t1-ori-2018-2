#include "index.h"

const char *_INDEXFNAME = "indice.bin";
const char *_INDEXFNAME = "indice_nome.bin";

FILE * create_primary_index(FILE *data_f) {
	// Abre o arquivo se já existir, cria se não
	FILE *file = fopen(_INDEXFNAME, "rb+");
	if(file == NULL)
		file = fopen(_INDEXFNAME, "w");
	if(file == NULL) {
		puts(ERR_FILE_NOT_FOUND);
		return;
	}

	// Lê arquivo de dados para inserir no índice
	rewind(data_f);
	Entry **entry_list;
	Entry *entry;
	while (read_entry(file, entry)) {

	};


}

FILE * create_name_index(FILE *data_f) {
	// Abre o arquivo se já existir, cria se não
	FILE *file = fopen(_NINDEXFNAME, "rb+");
	if(file == NULL)
		file = fopen(_NINDEXFNAME, "w");
	if(file == NULL) {
		puts(ERR_FILE_NOT_FOUND);
		return;
	}

	// Lê arquivo de dados para inserir no índice
	rewind(data_f);
	Entry **entry_list;
	Entry *entry;
	while (read_entry(file, entry)) {

	};


}