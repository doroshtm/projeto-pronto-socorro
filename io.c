#include "io.h"
#include <stdio.h>
#include <stdlib.h>

void carregarDados(LISTA_PACIENTE *lista,  TRIAGEM *triagem){
    
}

bool salvarDados(LISTA_PACIENTE *lista, TRIAGEM *triagem){
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
            fprintf(f,"\t\"nome\": \"%s\",\n",paciente_getnome(paciente));
            fprintf(f,"\t\"histórico\": {\n");
            PROCEDIMENTO *procedimento = paciente->historico->ultimoProcedimento;
            for(int j=0; j < paciente->historico->quantidadeProcedimentos; j++){
                fprintf(f,"\t\t\"procedimento\": \"%s\"", procedimento->texto);
                if(j < paciente->historico->quantidadeProcedimentos-1){
                    fprintf(f,",\n");
                }
                procedimento = procedimento->anterior;
            }
            fprintf(f,"\t\n},\n");
        }
        fseek(f,-1,SEEK_CUR);
        fprintf(f,"\n}");
        fprintf(f,"\n}");
    }
    fclose(f);
    //fim salvar fila
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    //Salvar lista
    f = fopen("lista.json", "w");
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
            struct procedimento_ *procedimento = atual->paciente->historico->ultimoProcedimento;
            for(int j=0; j< atual->paciente->historico->quantidadeProcedimentos; j++){
                fprintf(f, "\"procedimento\": \"%s\"", procedimento->texto);
                if(j < atual->paciente->historico->quantidadeProcedimentos-1){
                    fprintf(f,",\n");
                }
                procedimento = procedimento->anterior;
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