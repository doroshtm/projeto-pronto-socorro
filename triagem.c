#include"triagem.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// a triagem é uma fila (FIFO) de pacientes
struct triagem_ {
    PACIENTE *pacientes[100]; //100: valor arbitrário escolhido para a fila
    int proximo;
};

TRIAGEM *triagem_inicializar() {
    TRIAGEM *novaTriagem = malloc(sizeof(TRIAGEM));
    if(novaTriagem == NULL) {
        return NULL;
    }
    
    novaTriagem->proximo = 0;
    return novaTriagem;
}

bool triagem_inserir_paciente(TRIAGEM *triagem, PACIENTE *paciente) {
    if(triagem == NULL || triagem->proximo >= 100) {
        return false;
    }

    triagem->pacientes[triagem->proximo++] = paciente;
    return true;
}

PACIENTE *triagem_remover_paciente(TRIAGEM *triagem) {
    if(triagem == NULL || triagem->proximo == 0) {
        return NULL;
    }
    PACIENTE *removido = triagem->pacientes[0];
    
    // Desloca os pacientes para remover o primeiro da fila
    for(int i = 0; i < triagem->proximo - 1; ++i) {
        triagem->pacientes[i] = triagem->pacientes[i + 1];
    }
    --triagem->proximo;
    return removido;
}

bool triagem_fila_cheia(TRIAGEM *triagem) {
    return triagem != NULL && triagem->proximo >= 100;
}

bool triagem_fila_vazia(TRIAGEM *triagem) {
    return triagem == NULL || triagem->proximo == 0;
}

void triagem_mostrar_fila(TRIAGEM *triagem) {
    if(triagem == NULL || triagem->proximo == 0) {
        printf("A triagem está vazia!\n");
        return;
    }
    
    printf("Fila de espera:\n");
    for(int i = 0; i < triagem->proximo; ++i) {
        PACIENTE *paciente = triagem->pacientes[i];
        if(paciente == NULL) {
            printf("Posição %d: ERRO!\n", i + 1);
            continue;
        }
        printf("Posição %d: Paciente %s (ID %d)\n", i + 1, paciente_getnome(paciente), paciente_getid(paciente));
    }
}

bool triagem_apagar(TRIAGEM **triagem) {
    if(triagem == NULL || *triagem == NULL) {
        return false;
    }
    free(*triagem);
    *triagem = NULL;
    return true;
}

int triagem_getproximo(TRIAGEM *triagem){
    return triagem->proximo;
}

bool salvar_fila(TRIAGEM *triagem){
    //Salvar fila
    FILE *f = fopen("fila.json", "w");
    if(f == NULL){
        return false;
    }
    if(triagem != NULL && triagem->proximo != 0) {
        fprintf(f,"{\n");
        for(int i = 0; i < triagem->proximo; ++i) {
            PACIENTE *paciente = triagem->pacientes[i];
            if(paciente == NULL) {
                continue;
            }
            fprintf(f,"\t\"id\": \"%d\",\n",paciente_getid(paciente));
            fprintf(f,"\t\n},\n");
        }
        fseek(f,-1,SEEK_CUR);
        fprintf(f,"\n}\n}");
    }
    fclose(f);
    return true;
}

void carregar_fila(TRIAGEM *triagem, LISTA_PACIENTE *lista){
    if(triagem != NULL){
        FILE *f = fopen("fila.json", "r");
        if(f == NULL){
            return;
        }
        char buffer[101];
        int id;
        PACIENTE *paciente;
        while( fgets(buffer,100,f) != NULL){
            if(strstr(buffer, "\"id\":")){
                sscanf(buffer,"%*[^:]: %d", &id);
            }
            paciente = lista_paciente_buscar(lista, id);
            triagem_inserir_paciente(triagem, paciente);
        }
    }
}