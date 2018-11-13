#include "file.h"
#include "entry.h"

/** ********* FUNÇÕES COMPLEXAS *********
[Inserção]
Recebe vários registros novos e insere no primeiro espaço vazio, caso não exista um espaço vazio, adiciona ao fim.
Parâmetros:
	qty. Qtd de registros
	regs. Vetor de registros
**/
void insert(size_t qty, Entry *regs) {
	// Abre o arquivo se já existir, cria se não
	FILE *file = fopen(_FNAME, "rb+");
	if(file == NULL)
		file = fopen(_FNAME, "w");
	if(file == NULL) {
		puts(ERR_FILE_NOT_FOUND);
		return;
	}
	
	Entry buffer;
	rewind(file);

	// Tenta reaproveitar registros removidos
	size_t read_bytes;
	while(qty >= 1 && read_entry(file, &buffer)) {
		dprintf("Passeando por uma entry existente!\n");
		if(buffer.removed) {
			dprintf("Ei um cara perdido!\n");
			write_entry(file, regs, true);
			regs++;
			qty--;
		}
	}

	// Grava os que não puderam reaproveitar espaço no final
	while(qty >= 1) {
		dprintf("Ninguem fica pra tras!\n");
		write_entry(file, regs, false);
		regs++;
		qty--;
	}

	// Finaliza escrita e fecha handler do sistema
	fclose(file);
}

bool find_by_entry_number(unsigned int number, Entry *result, FILE *file, size_t *pos) {
	rewind(file);

	while(read_entry(file, result) && number > 0) { // MEMORY LEAK!
		*pos = ftell(file);
		number--;
	}
	
	return (number == 0);
}

bool find_by_entry_key(unsigned int key, Entry *result, FILE *file, size_t *pos) {
	rewind(file);
	
	while(read_entry(file, result) && (result->removed || result->key != key)) {
		*pos = ftell(file);
	}

	return (result->key == key);
}

bool delete_entry(FILE *file, size_t pos, size_t size, size_t next) {
	if(fseek(file, pos, SEEK_BEGIN) != 0)
		return false;
	Removed data = (Removed){true, size, next};
	fwrite(&data, sizeof(Removed), 1, file);
	return true;
}