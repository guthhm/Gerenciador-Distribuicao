CC=gcc
CFLAGS=-I.
DEPS = history.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gerenciador: distribuicao.c
	gcc -W -o gerenciador.out distribuicao.c
	./gerenciador.out