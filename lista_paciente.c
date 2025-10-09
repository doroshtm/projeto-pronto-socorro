#include"paciente.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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
    novoNo->proximo = NULL;
    if(lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    } else {
        lista->ultimo->proximo = novoNo;
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
            printf("aqui...");
            if(anterior == NULL) {
                printf("aqui2...");
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

int lista_paciente_gerar_id_unico(LISTA_PACIENTE *lista) {
    return lista->ultimo == NULL ? 0 : paciente_getid(lista->ultimo->paciente) + 1;
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
            fprintf(f,"\t\n}");
            atual = atual->proximo;
            if(atual != NULL){
                fprintf(f, ",\n");
            }
        }
    }
    fclose(f);
    return true;
}

void carregar_lista(LISTA_PACIENTE *lista){
    if(lista!=NULL){
        FILE *f = fopen("lista.json", "r");
        if(f == NULL){
            return;
        }
        char buffer[101], nome[101], procedimento[11];
        int id;
        PACIENTE *paciente;
        while(fgets(buffer, 100, f) != NULL){
            if(strstr(buffer, "\"id\":")){
                sscanf(buffer, "%*[^:]: %d", &id);
            }else if(strstr(buffer, "\"nome\":")){
                sscanf(buffer, "%*[^:]: %s", nome);
                paciente = paciente_criar(nome, lista, id);
            }else if(strstr(buffer, "\"historico\":")){
                while(fgets(buffer, 100, f) != NULL && !strstr(buffer, "}")){
                    if(strstr(buffer, "\"procedimento\":")){
                        sscanf(buffer, "%*[^:]: %s", procedimento);
                        historico_inserir(paciente_gethistorico(paciente), procedimento);
                    }
                }
                historico_inverter(paciente_gethistorico(paciente));//O histórico pego dos dados vem invertido
                lista_paciente_inserir(lista, paciente);
                paciente = NULL;
                free(paciente);
            }
        }
    }
}