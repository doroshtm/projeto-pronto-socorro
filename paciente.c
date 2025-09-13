#include"paciente.h"
#include"historico.h"

struct paciente_ {
    int id;
    char nome[100];
    HISTORICO *historico;
};

PACIENTE *paciente_criar(char nome[100]) {
    PACIENTE *novo = malloc(sizeof(PACIENTE));
    if (novo == NULL) {
        return NULL;
    }
    novo->id = gerar_id_unico();
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

paciente_gethistorico(PACIENTE *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->historico;
}