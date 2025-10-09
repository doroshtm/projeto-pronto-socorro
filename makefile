all: historico.o lista_paciente.o paciente.o triagem.o main.o
	gcc historico.o lista_paciente.o paciente.o triagem.o main.o -o main -std=c99 -Wall

historico.o:
	gcc -c historico.c -o historico.o -std=c99 -Wall

lista_paciente.o:
	gcc -c lista_paciente.c -o lista_paciente.o -std=c99 -Wall

paciente.o:
	gcc -c paciente.c -o paciente.o -std=c99 -Wall
	
triagem.o:
	gcc -c triagem.c -o triagem.o -std=c99 -Wall

main.o:
	gcc -c main.c -o main.o -std=c99 -Wall

run:
	./main

clean:
	rm *.o
