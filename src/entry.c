#include "entry.h"

//Objetivo:   Le, a partir do arquivo, um registro.
//Parametros: Arquivo, registro (onde sera armazenado o resultado).
//Retorno:    Valor Booleano que indica se foi possivel a leitura.
bool read_entry(FILE *file, Entry *dst) {
#if FIXED_SIZE == 1
	// Lê o registro inteiro como um todo
	return fread(dst, sizeof(Entry), 1, file) == 1;
#else
	// Gambi pra continuarmente escrever diretamente pro struct
	void *buffer_d = dst; 

	// Lê o flag de removido
	if(fread(buffer_d, sizeof((Entry){0}.removed), 1, file) != 1)
		return false;
	buffer_d += sizeof((Entry){0}.removed);

	if (!removed) {
		// Lê a chave
		if(fread(buffer_d, sizeof((Entry){0}.key), 1, file) != 1)
			return false;
		buffer_d += sizeof((Entry){0}.key);

		// Lê os 7 campos de texto
		char aatrs = 7;
		while(aatrs > 0) {
			// Lê o tamanho
			if(fread(buffer_d, sizeof((Sstr){0}.length), 1, file) != 1)
				return false;
			// Lê o texto
			char *newstr = malloc(*((size_t*)buffer_d) * sizeof(char));
			buffer_d += sizeof((Sstr){0}.length);
			*(char**)buffer_d = newstr;
			buffer_d += sizeof((Sstr){0}.data);
			// Conclui este
			aatrs--;
		}

	} else {
		// Lê o tamanho e o próximo
		size_t removed_data = sizeof((Removed){0}.size) + sizeof((Removed){0}.next);
		if(fread(buffer_d, removed_data, 1, file) != 1)
			return false;
		// Vai manualmente pro seguinte
		fseek(file, ((Removed*)dst)->next, SEEK_BEGIN);
	}
	return true;
#endif
}

//Objetivo:   Inserir no arquivo, um novo registro.
//Parametros: Arquivo, registro, flag para indicar.
//Retorno:    Nao ha.
void write_entry(FILE *file, Entry *src, bool reuse) {
#if FIXED_SIZE == 1
	if (reuse)
		fseek(file, - sizeof(Entry), SEEK_CUR);
	fwrite(src, sizeof(Entry), 1, file);
#else
	if(src->removed) {
		fwrite(src, sizeof(Removed), 1, file);
	} else {
		fwrite(src, sizeof((Entry){0}.removed), 1, file);
		// { LÊ A DATA, CONTA O TAMANHO, ESCREVE O TAMANHO, ESCREVE A DATA }
	}
#endif
}

//Objetivo:   Exibir no console, um registro. (ou uma mensagem caso tenha sido deletado).
//Parametros: Registro.
//Retorno:    Nao ha.
void print_entry(Entry *entry) {
	int entry_number = 0;
	if(entry->removed) {
		Removed *removed = (Removed*) entry;
		printf("Registro removido! (%lu bytes -> next at %lu)\n"
			, removed->size, removed->next);
	}
	else
		printf("Registro #\n"
			"\tChave: %u,\n"
			"\tNome: %s,\n"
			"\tSobrenome: %s,\n"
			"\tEndereco: %s,\n"
			"\tCidade: %s,\n"
			"\tEstado: %s,\n"
			"\tCEP: %s,\n"
			"\tTelefone: %s\n",
			entry->key,
#if FIXED_SIZE == 1
			entry->firstname,
			entry->lastname,
			entry->address,
			entry->city,
			entry->uf,
			entry->zip,
			entry->phone
#else
			entry->firstname.data,
			entry->lastname.data,
			entry->address.data,
			entry->city.data,
			entry->uf.data,
			entry->zip.data,
			entry->phone.data
#endif
		);
}