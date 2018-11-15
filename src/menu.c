#include "menu.h"
#include "entry.h"
#include "file.h"

//Objetivo:   Perguntar ao usuario, o numero do registro que ele deseja encontrar.
//Parametros: Nao ha.
//Retorno:    Numero digitado pelo usuario.
size_t ask_entry_number() {
	size_t out = 0L;
	if(!quiet) printf("> Qual registro ver?: ");
	char buffer[32] = "";
	fgets(buffer, sizeof(char) * 32, stdin);
	sscanf(buffer, "%lu", &out);
	return out;
}

//Objetivo:   Perguntar ao usuario, a chave do registro que ele deseja encontrar.
//Parametros: Nao ha.
//Retorno:    Chave digitada pelo usuario.
unsigned int ask_key_number(){
	unsigned int key;
	if(!quiet) printf("> Informe a chave do registro: ");
	char buffer[32] = "";
	fgets(buffer, sizeof(char) * 32, stdin);
	sscanf(buffer, "%u", &key);
	return key;
}

//Objetivo:   Encontrar e monstrar um registro pelo seu numero.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void find_and_print_entry_by_number() {
	Entry entry;
	FILE *file = fopen(_FNAME, "rb");
	rewind(file);
	int entry_number = ask_entry_number();
	size_t pos;
	if(find_by_entry_number(entry_number - 1, &entry, file, &pos)) {
		print_entry(&entry);
	} else {
		printf("Registro não encontrado");
	} 
}

//Objetivo:   Encontrar e monstrar um registro pela sua chave.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void find_and_print_entry_by_key(){
	Entry entry;
	FILE *file = fopen(_FNAME, "rb");
	unsigned int key = ask_key_number();
	size_t pos;
	if(find_by_entry_key(key, &entry, file, &pos)){
		print_entry(&entry);
	} else {
		printf("Registro não encontrado");
	}
}

//Objetivo:   Encontrar e apagar um registro pelo sua chave.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void find_and_delete_entry_by_key(){
	Entry entry;
	FILE *file = fopen(_FNAME, "rwb+");
	unsigned int key = ask_key_number();
	size_t pos, next;
	if(find_by_entry_key(key, &entry, file, &pos)){
		// Essa gambi ficou linda que até arde os olhos! (*-*)
		fseek(file, pos, SEEK_SET);
		read_entry(file, &entry);
		next = ftell(file);
		delete_entry(file, pos, next - pos, next);
	} else {
		printf("Registro não encontrado");
	}
}

//Objetivo:   Encontrar e monstrar um registro pelo campo nome.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void find_and_print_entry_by_firstname(){
	Entry *entry;
	FILE *file = fopen(_FNAME, "rb");
	rewind(file);
	
}

//Objetivo:   Alocar uma sized string de acordo com a entrada do usuario.
//Parametros: Ponteiro para sized string.
//Retorno:    Nao ha.
void ask_text(Sstr *dest) {
#if FIXED_SIZE == 1
	gets(dest);
#else
	char buffer[512];
	fgets(buffer, sizeof(char) * 512, stdin);
	dest->length = strlen(buffer);
	dest->data = (char*) malloc(dest->length * sizeof(char));
	strcpy(dest->data, buffer);
#endif	
}

//Objetivo:   Cadastrar campos do registro de acordo com a entrada do usuario.
//Parametros: Ponteiro para registro;
//Retorno:    Nao ha.
void ask_entry(Entry *dest) {
	dest->removed = false;
	if(!quiet) printf("Novo registro:\n\t> Chave: ");
	char buffer[32] = "";
	fgets(buffer, sizeof(char) * 32, stdin);
	sscanf(buffer, "%u", &(dest->key));
	if(!quiet) printf("\t> Nome: ");
	ask_text((char**)&(dest->firstname));
	if(!quiet) printf("\t> Sobrenome: ");
	ask_text((char**)&(dest->lastname));
	if(!quiet) printf("\t> Endereço: ");
	ask_text((char**)&(dest->address));
	if(!quiet) printf("\t> Cidade: ");
	ask_text((char**)&(dest->city));
	if(!quiet) printf("\t> UF: ");
	ask_text((char**)&(dest->uf));
	if(!quiet) printf("\t> CEP: ");
	ask_text((char**)&(dest->zip));
	if(!quiet) printf("\t> Telefone: ");
	ask_text((char**)&(dest->phone));
}

//Objetivo:   Perguntar ao usuario, quantos registros serao inseridos.
//Parametros: Nao ha.
//Retorno:    Quantidade inserida pelo usuario.
size_t ask_entries_qty() {
	size_t out = 0L;
	if(!quiet) printf("> Quantos registros para adicionar?: ");
	char buffer[32] = "";
	fgets(buffer, sizeof(char) * 32, stdin);
	sscanf(buffer, "%lu", &out);
	return out;
}

//Objetivo:   Fazer a insercao dos registros no arquivo, de acordo com as entradas do usuario.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void do_insert() {
	size_t qty = ask_entries_qty();
	Entry buffer;
	while(qty > 0) {
		ask_entry(&buffer);
		if (find_by_entry_key(buffer.key, NULL, NULL)) {
			insert(1, &buffer);
		} else {
			printf("Entrada com chave repetida! Skiping...\n");
		};
		qty--;
	}
}


//Objetivo:   Listar todos registros que estão presentes no arquivo.
//Parametros: Nao ha.
//Retorno:    Nao ha.
void do_list_all() {
	Entry entry;
	bool list_entries = true;
	FILE *file = fopen(_FNAME, "rb");
	//rewind(file);
	while (read_entry(file, &entry) && list_entries) {
		print_entry(&entry);
		if(!quiet) {
			printf("[n] Proximo registro");
			char buffer[4];
			fgets(buffer, sizeof(char) * 4, stdin);
			if(buffer[0] == 'c') {
				list_entries = false;
			}
		}
		printf("\n");
	}
}


//Objetivo:   Perguntar ao usuario, qual tarefa ele deseja realizar
//Parametros: Nao ha.
//Retorno:    Nao ha.
char ask_task() {
	if(!quiet)
		puts("Escolha uma tarefa:\n"
			"\t[i]\tInserir um ou mais registros\n"
			"\t[b]\tVisualizar todos os registros\n"
			"\t[e]\tBuscar um registro por entrada\n"
			"\t[k]\tBuscar um registro por chave\n"
			"\t[n]\tBuscar um registro por nome\n"
			"\t[d]\tRemover um registro pela chave\n"
			"\t[v]\tLimpar registros removidos (Reduz tamanho do arquivo)\n"
			"> Entre a tarefa desejada [i/b/e/k/n/d/v]: "
			);
	char buffer[4];
	fgets(buffer, sizeof(char) * 4, stdin);
	return buffer[0];
}