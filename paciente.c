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

PACIENTE *paciente_criar(char nome[100], LISTA_PACIENTE *lista, int id) {
    PACIENTE *novo = malloc(sizeof(PACIENTE));
    if (novo == NULL) {
        return NULL;
    }
    if(id<-1){//A partir de -2 para baixo conta como se o paciente existisse e será carregado
        novo->id = lista_paciente_gerar_id_unico(lista);
    }
    strncpy(novo->nome, nome, 100);
    novo->historico = historico_criar();
    return novo;
}

bool paciente_apagar(PACIENTE **paciente) {
    if (paciente == NULL || *paciente == NULL) {
        return false;
    }
    historico_apagar(&(*paciente)->historico);
    free(*paciente);
    *paciente = NULL;
    return true;
}

int paciente_getid(PACIENTE *paciente) {
    return paciente->id;
}

char *paciente_getnome(PACIENTE *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->nome;
}

HISTORICO *paciente_gethistorico(PACIENTE *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->historico;
}