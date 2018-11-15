PROJECT=oriT1
INSTALL_PATH?=/usr/local


CFLAGS=-Wno-discarded-qualifiers -g -I./include -O3
CC=gcc
BUNDLE_AR=ar rcs

bin/%.o: src/%.c
	${CC} -g -o $@ -c $< ${CFLAGS}

bin/main.exe: bin/main.o bin/menu.o bin/entry.o bin/file.o bin/index.o
	${CC} -g bin/main.o bin/menu.o bin/entry.o bin/file.o bin/index.o ${CFLAGS} -o $@

.PHONY: clean install

all: bin/main.exe

test: bin/main.exe
	bin/main.exe < tests/1.in

clean:
	rm bin/*.exe