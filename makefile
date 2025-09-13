all: intencadeado.o historico.o paciente.o triagem.o main.o
	gcc historico.o intencadeado.o paciente.o triagem.o main.c -o main -std=c99 -Wall -lm

historico.o:
	gcc -c ponto.c -o ponto.o
	
intencadeado.o:
	gcc -c intencadeado.c -o intencadeado.o

paciente.o:
	gcc -c paciente.c -o paciente.o
	
triagem.o:
	gcc -c triagem.c -o triagem.o

run:
	./main

clean:
	rm historico.o
	rm triagem.o
	rm intencadeado.o
	rm paciente.o
	rm main
