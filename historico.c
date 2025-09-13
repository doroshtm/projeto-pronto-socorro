#include "historico.h"

struct historico_ {
    struct procedimento_ *ultimoProcedimento;
    int quantidadeProcedimentos;
};

typedef struct procedimento_ {
    char texto[10];
    struct procedimento_ *anterior;
} PROCEDIMENTO;

HISTORICO *historico_criar() {
    HISTORICO *novo = malloc(sizeof(HISTORICO));
    if(novo == NULL) {
        return NULL;
    }
    novo->ultimoProcedimento = NULL;
    novo->quantidadeProcedimentos = 0;
    return novo;
}

bool historico_inserir(HISTORICO *historico, char *procedimento) {
    if(historico == NULL) {
        historico = malloc(sizeof(HISTORICO));
        if(historico == NULL) {
            return false;
        }
    }
    if(historico_cheio(historico)) {
        return false;
    }

    if(procedimento != NULL) {
        PROCEDIMENTO *novoProcedimento = malloc(sizeof(PROCEDIMENTO));
        if(novoProcedimento == NULL) {
            return false;
        }
        strncpy(novoProcedimento->texto, procedimento, 100);
        novoProcedimento->anterior = historico->ultimoProcedimento;
        historico->ultimoProcedimento = novoProcedimento;
    }

    ++historico->quantidadeProcedimentos;

    return true;
}

bool historico_retirar(HISTORICO *historico) {
    if (historico == NULL) {
        return false;
    }

    PROCEDIMENTO *ultimo = historico->ultimoProcedimento;
    if (ultimo != NULL) {
        historico->ultimoProcedimento = ultimo->anterior;
        free(ultimo);
        ultimo = NULL;
        --historico->quantidadeProcedimentos;
    }
    return true;
}

char **historico_consultar_procedimento(HISTORICO *historico) {
    if(historico == NULL) {
        return NULL;
    }
    
    char **procedimentos = malloc(10 * sizeof(char *));
    if(procedimentos == NULL) {
        return NULL;
    }

    int i = 0;
    PROCEDIMENTO *atual = historico->ultimoProcedimento;
    while(atual != NULL && i < 10) {
        procedimentos[i] = atual->texto;
        atual = atual->anterior;
        ++i;
    }

    return procedimentos;
}

bool historico_cheio(HISTORICO *historico) {
    if (historico == NULL) {
        return false;
    }

    return (historico->quantidadeProcedimentos >= 10);
}

bool historico_vazio(HISTORICO *historico) {
    if (historico == NULL || historico->ultimoProcedimento == NULL || historico->quantidadeProcedimentos == 0) {
        return true;
    }
    
    return false;
}

bool historico_apagar(HISTORICO **historico) {
    if (historico == NULL || *historico == NULL) {
        return false;
    }

    while (!historico_vazio(*historico)) {
        if(!historico_retirar(*historico)) {
            return false;
        }
    }

    free(*historico);
    *historico = NULL;
    return true;
}