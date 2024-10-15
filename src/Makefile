# Makefile for compiling and testing tokenizer

all: tokenizer

tokenizer: tokenizer.o history.o
	gcc -o tokenizer tokenizer.o history.o

tokenizer.o: tokenizer.h tokenizer.c

history.o: history.h history.c

run:
	./tokenizer

clean:
	rm -f *.o tokenizer
