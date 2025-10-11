#include"paciente.h"
#include"historico.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct paciente_ {
    int id;
    char nome[100];
    HISTORICO *historico;
};

//Função para criar paciente
PACIENTE *paciente_criar(char nome[], LISTA_PACIENTE *lista, int id) {
    //Alocação do ponteiro para paciente
    PACIENTE *novo = malloc(sizeof(PACIENTE));
    if (novo == NULL) {
        return NULL;
    }
    //Caso o id seja menor que 0 será gerado um novo id
    if(id<0){
        novo->id = lista_paciente_gerar_id_unico(lista);
    }else{
        //O caso contrário é quando o paciente foi carregado da lista salva no JSON
        //Portanto não precisamos criar novos ids 
        novo->id = id;
    }
    strncpy(novo->nome, nome, 100);
    novo->historico = historico_criar();
    return novo;
}

//Apagar paciente
bool paciente_apagar(PACIENTE **paciente) {
    if (paciente == NULL || *paciente == NULL) {
        return false;
    }
    //Antes de liberar a memória é necessário apagar o histórico
    historico_apagar(&(*paciente)->historico);
    free(*paciente);
    *paciente = NULL;
    return true;
}

//Retorna o id do paciente
int paciente_getid(PACIENTE *paciente) {
    return paciente->id;
}

//Retorna o nome do paciente
char *paciente_getnome(PACIENTE *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->nome;
}

//Retorna no histórico do paciente
HISTORICO *paciente_gethistorico(PACIENTE *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->historico;
}