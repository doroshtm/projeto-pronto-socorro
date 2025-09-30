#include"paciente.h"
#include"lista_paciente.h"
#include"historico.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct no_ {
    PACIENTE *paciente;
    struct no_ *proximo;
} NO;

struct lista_paciente_ {
    NO *primeiro;
    NO *ultimo;
};

LISTA_PACIENTE *lista_paciente_inicializar() {
    LISTA_PACIENTE *novaLista = malloc(sizeof(LISTA_PACIENTE));
    if(novaLista == NULL) {
        return NULL;
    }
    novaLista->primeiro = NULL;
    novaLista->ultimo = NULL;
    return novaLista;
}

bool lista_paciente_inserir(LISTA_PACIENTE *lista, PACIENTE *paciente) {
    if(paciente == NULL) {
        return false;
    }
    NO *novoNo = malloc(sizeof(NO));
    if(novoNo == NULL) {
        return false;
    }
    novoNo->paciente = paciente;
    novoNo->proximo = lista->primeiro;
    if(lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    }
    lista->ultimo = novoNo;

    return true;
}

bool lista_paciente_remover(LISTA_PACIENTE *lista, PACIENTE *paciente) {
    if(lista == NULL || paciente == NULL) {
        return false;
    }

    NO *atual = lista->primeiro;
    NO *anterior = NULL;

    while(atual != NULL) {
        if(atual->paciente == paciente) {
            if(anterior == NULL) {
                lista->primeiro = atual->proximo;
            }else {
                anterior->proximo = atual->proximo;
            }
            if(atual == lista->ultimo) {
                lista->ultimo = anterior;
            }
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return false;
}

PACIENTE *lista_paciente_buscar(LISTA_PACIENTE *lista, int id) {
    if(lista == NULL || id < 0) {
        return NULL;
    }

    NO *atual = lista->primeiro;

    while(atual != NULL) {
        if(paciente_getid(atual->paciente) == id) {
            return atual->paciente;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void lista_paciente_listar(LISTA_PACIENTE *lista) {
    NO *atual = lista->primeiro;

    if(atual == NULL || atual->paciente == NULL) {
        printf("Não há nenhum paciente!");
        return;
    }

    int i = 1;
    while(atual != NULL) {
        printf("Paciente %d:\n",i);
        printf("ID: %d\n",paciente_getid(atual->paciente));
        printf("Nome: %s\n",paciente_getnome(atual->paciente));

        atual = atual->proximo;
        ++i;
    }
    printf("\n");
}

bool lista_paciente_apagar(LISTA_PACIENTE **lista) {
    if(lista == NULL || *lista == NULL) {
        return false;
    }

    NO *atual = (*lista)->primeiro;
    NO *proximo;

    while(atual != NULL) {
        proximo = atual->proximo;
        paciente_apagar(&atual->paciente);
        free(atual);
        atual = proximo;
    }

    free(*lista);
    *lista = NULL;
    return true;
}

bool salvar_lista(LISTA_PACIENTE *lista){
    //Salvar lista
    FILE *f = fopen("lista.json", "w");
    if(f == NULL){
        return false;
    }
    NO *atual = lista->primeiro;
    if(atual != NULL && atual->paciente != NULL) {
        fprintf(f,"{\n");
        while(atual != NULL) {
            fprintf(f,"\t\"id\": \"%d\",\n", paciente_getid(atual->paciente));
            fprintf(f,"\t\"nome\": \"%s\",\n", paciente_getnome(atual->paciente));
            fprintf(f,"\t\"histórico\": {\n");
            PROCEDIMENTO *procedimento = historico_getultimo(paciente_gethistorico(atual->paciente));
            for(int j=0; j< historico_getquantidade(paciente_gethistorico(atual->paciente)); j++){
                fprintf(f, "\"procedimento\": \"%s\"", procedimento_gettexto(procedimento));
                if(j < historico_getquantidade(paciente_gethistorico(atual->paciente))-1){
                    fprintf(f,",\n");
                }
                procedimento = procedimento_getanterior(procedimento);
            }
            fprintf(f,"\t\n},\n");
            atual = atual->proximo;
        }
        fseek(f,-1,SEEK_CUR);
        fprintf(f,"\n}");
    }
    fclose(f);
    return true;
}