/*
[ Trabalho ORI - T1 2018/11/07 ]
	Autores:
		Luiz Guilherme Duarte
		Pedro Henrique Lara Campos
		Yuji Aciole
*/

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include "menu.h"

// Globais
#if FIXED_SIZE == 1
const char *_FNAME = "arquivo.bin";
#else
const char *_FNAME = "arquivo.txt";
#endif
const char *ERR_FILE_NOT_FOUND = "Impossível editar arquivo!";
bool quiet = false;

// MAIN
int main(int argc,char **argv){
	bool invalid_menu = true;
	quiet = (argc >= 2);
	while(invalid_menu) {
		invalid_menu = false;
		switch(quiet ? argv[1][0] : ask_task()) {
			case 'i': // INSERIR
				do_insert();
				break;
			case 'b':
				do_list_all();
				break;
			case 'e':			
				find_and_print_entry_by_number();
				break;
			case 'k':
				find_and_print_entry_by_key();
				break;
			case 'd':
				find_and_delete_entry_by_key();
				break;
			default:
				quiet = false;
				invalid_menu = true;
				puts("Tarefa desconhecida!");
				if(quiet) {
					puts("Forma de uso: ./bin/main.exe [i/b/e/k/n/d/v]");
					return -1;
				}
		}
	}

	return 0;
}