#include "file.h"
#include "entry.h"

/** ********* FUNÇÕES COMPLEXAS *********
[Inserção]
Recebe vários registros novos e insere no primeiro espaço vazio, caso não exista um espaço vazio, adiciona ao fim.
Parâmetros:
	qty. Qtd de registros
	new. Vetor de registros
**/
void insert(FILE* file, size_t qty, Entry *new) {
	Entry buffer;
	rewind(file);

	// Tenta reaproveitar registros removidos
	size_t read_bytes, last_pos = 0;
	while(qty >= 1 && read_entry(file, &buffer)) {
		dprintf("Passeando por uma entry existente!\n");
		if(buffer.removed) {
			dprintf("Ei um cara perdido!\n");
			fseek(file, last_pos, SEEK_CUR);
			write_entry(file, new);
			new++;
			qty--;
		}
		last_pos = ftell(file);
	}

	fseek(file, 0, SEEK_END);

	// Grava os que não puderam reaproveitar espaço no final
	while(qty >= 1) {
		dprintf("Ninguem fica pra tras!\n");
		write_entry(file, new);
		new++;
		qty--;
	}
}

//Objetivo:   Encontrar um registro, a partir do seu numero (posicao) no arquivo, armazena-lo guardando tambem sua posicao.
//Parametros: Numero, ponteiro para armazenar o registro, arquivo, ponteiro para armazenar posicao relativa do registro no arquivo.
//Retorno:    Booelano, indicando se foi ou nao encontrado o registro.
bool find_by_entry_number(unsigned int number, Entry *result, FILE *file, size_t *pos) {
	rewind(file);

	while(read_entry(file, result) && number > 0) { // MEMORY LEAK!
		*pos = ftell(file);
		number--;
	}
	
	return (number == 0);
}

//Objetivo:   Encontrar um registro, a partir da sua chave, armazena-lo guardando tambem sua posicao.
//Parametros: Chave, ponteiro para armazenar o registro, arquivo, ponteiro para armazenar posicao relativa do registro no arquivo.
//Retorno:    Booelano, indicando se foi ou nao encontrado o registro.
bool find_by_entry_key(unsigned int key, Entry *result, FILE *file, size_t *pos) {
	rewind(file);
	
	while(read_entry(file, result) && (result->removed || result->key != key)) {
		*pos = ftell(file);
	}

	return (result->key == key);
}

//Objetivo:   Apagar registro.
//Parametros: Arquivo, posicao do registro, seu tamanho,  posicao do proximo registro.
//Retorno:    Booelano, se foi possivel ou nao apagar o registro.
bool delete_entry(FILE *file, size_t pos, size_t size) {
	if(fseek(file, pos, SEEK_SET) != 0)
		return false;
	Entry data = (Entry){0};
	*((Removed*)&data) = (Removed){true, size};
	size_t written = write_entry(file, &data);
#if FIXED_SIZE != 1
	fseek(file, size - written, SEEK_CUR);
#endif
	return written > 0;
}