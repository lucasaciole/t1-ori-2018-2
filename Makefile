CFLAGS=-Wno-discarded-qualifiers -g -I./include -O3
CC=gcc

bin/fixo.exe:
	${CC} -g src/main.c src/menu.c src/entry.c src/file.c ${CFLAGS} -o $@

bin/delimitado.exe:
	${CC} -DDELIMITED -g src/main.c src/menu.c src/entry.c src/file.c ${CFLAGS} -o $@

.PHONY: clean

fixo: bin/fixo.exe
delimitado: bin/delimitado.exe

all: bin/fixo.exe bin/delimitado.exe

test: all
	bin/fixo.exe i < tests/popula.in
	bin/delimitado.exe i < tests/popula.in

clean:
	rm bin/*
	rm arquivo.*