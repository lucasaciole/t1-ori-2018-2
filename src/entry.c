#include "entry.h"

//Objetivo:   Le, a partir do arquivo, um registro.
//Parametros: Arquivo, registro (onde sera armazenado o resultado).
//Retorno:    Valor Booleano que indica se foi possivel a leitura.
bool read_entry(FILE *file, Entry *dst) {
#if FIXED_SIZE == 1
	// Lê o registro inteiro como um todo
	return fread(dst, sizeof(Entry), 1, file) == 1;
#else
	char buffer[512] = "", *fixnl;
	fgets(buffer, 512 * sizeof(char), file);
	dst->removed = (buffer[0] == 'r');
	if(dst->removed) {
		Removed *rem = (Removed*) dst;
		fgets(buffer, 512 * sizeof(char), file);
		sscanf(buffer, "%lu", &(rem->size));
		fseek(file, rem->size-2-strlen(buffer), SEEK_CUR);
	} else {
		if(sscanf(buffer, "%u", &(dst->key)) != 1)
			// Arquivo provavelmente corrompido, ou a gente foi parar no meio de um registro
			return false;
		Sstr *data=&(dst->lastname), *last_data=&(dst->phone);
		while(data <= last_data) {
			fgets(buffer, 512 * sizeof(char), file);
			fixnl = strchr(buffer, '\n');
			if(fixnl > buffer) *fixnl = 0;
			data->length = strlen(buffer);
			data->data = (char*) malloc(data->length*sizeof(char)+1);
			memcpy(data->data, buffer, data->length*sizeof(char)+1);
			data++;
		}
		fseek(file, 2, SEEK_CUR); //pula o "#\n"
	}
	return true;
#endif
}

//Objetivo:   Inserir no arquivo, um novo registro.
//Parametros: Arquivo, registro novo.
//Retorno:    Nao ha.
size_t write_entry(FILE *file, Entry *src) {
#if FIXED_SIZE == 1
	fwrite(src, sizeof(Entry), 1, file);
	return sizeof(Entry);
#else
	char buffer[1024]="";
	if (src->removed) {
		sprintf(buffer, "r\n%lu\n#\n", ((Removed*)src)->size);
	} else {
		sprintf(
			buffer,
			"%u\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n#\n",
			src->key,
			src->firstname.data,
			src->lastname.data,
			src->address.data,
			src->city.data,
			src->uf.data,
			src->zip.data,
			src->phone.data
			);
	}
	fprintf(file, buffer);
	return strlen(buffer) * sizeof(char);
#endif
}

//Objetivo:   Exibir no console, um registro. (ou uma mensagem caso tenha sido deletado).
//Parametros: Registro.
//Retorno:    Nao ha.
void print_entry(Entry *entry) {
	int entry_number = 0;
	if(entry->removed) {
		Removed *removed = (Removed*) entry;
		printf("Registro removido! (%lu bytes)\n",
			removed->size);
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