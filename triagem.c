#include"triagem.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// a triagem é uma fila (FIFO) de pacientes
struct triagem_ {
    PACIENTE *pacientes[100]; //100: valor arbitrário escolhido para a fila
    int proximo;
};

//Função para criar a triagem
TRIAGEM *triagem_inicializar() {
    TRIAGEM *novaTriagem = malloc(sizeof(TRIAGEM));
    if(novaTriagem == NULL) {
        return NULL;
    }
    
    novaTriagem->proximo = 0;
    return novaTriagem;
}

//Função para inserir um paciente
bool triagem_inserir_paciente(TRIAGEM *triagem, PACIENTE *paciente) {
    if(triagem == NULL || triagem->proximo >= 100) {
        return false;
    }
    //Ele é colocado ao final da fila
    triagem->pacientes[triagem->proximo++] = paciente;
    return true;
}

//Triagem para remover paciente da fila
PACIENTE *triagem_remover_paciente(TRIAGEM *triagem) {
    if(triagem == NULL || triagem->proximo == 0) {
        return NULL;
    }
    //O paciente removido é sempre o primeiro, pois
    //como é uma fila temos que o primeiro a entrar
    //Também é o primeiro a sair
    PACIENTE *removido = triagem->pacientes[0];
    
    // Desloca os pacientes para remover o primeiro da fila
    for(int i = 0; i < triagem->proximo - 1; ++i) {
        triagem->pacientes[i] = triagem->pacientes[i + 1];
    }
    --triagem->proximo;
    return removido;
}

//Função para verificar se a fila está cheia
bool triagem_fila_cheia(TRIAGEM *triagem) {
    return triagem != NULL && triagem->proximo >= 100;
}

//Função para verificar se a fila está vazia
bool triagem_fila_vazia(TRIAGEM *triagem) {
    return triagem == NULL || triagem->proximo == 0;
}

//Função para printar a lista de pacientes
void triagem_mostrar_fila(TRIAGEM *triagem) {
    if(triagem == NULL || triagem->proximo == 0) {
        printf("A triagem está vazia!\n");
        return;
    }
    
    printf("Fila de espera:\n");
    //triagem->proximo armazena a proxima posição que um paciente será incluído na fila
    for(int i = 0; i < triagem->proximo; ++i) {
        PACIENTE *paciente = triagem->pacientes[i];
        if(paciente == NULL) {
            //Reportagem de posição com paciente inválido
            printf("Posição %d: ERRO!\n", i + 1);
            continue;
        }
        //Apresenta os dados do paciente na tela
        printf("Posição %d: Paciente %s (ID %d)\n", i + 1, paciente_getnome(paciente), paciente_getid(paciente));
    }
}

//Função para apagar paciente, recebe ponteiro para ponteiro para poder apagar o ponteiro original
//Não sua cópia.
bool triagem_apagar(TRIAGEM **triagem) {
    if(triagem == NULL || *triagem == NULL) {
        return false;
    }
    free(*triagem);
    *triagem = NULL;
    return true;
}

//Função para retornar a próxima posição livre na fila
int triagem_getproximo(TRIAGEM *triagem){
    return triagem->proximo;
}

bool salvar_fila(TRIAGEM *triagem){
    //Inicialização do ponteiro para escrita do arquivo
    FILE *f = fopen("fila.json", "w");
    if(f == NULL){
        return false;
    }
    fprintf(f, "[");//Início da escrita em formato JSON
    if(triagem != NULL && triagem->proximo != 0) {
        for(int i = 0; i < triagem->proximo; ++i) {
            PACIENTE *paciente = triagem->pacientes[i];//Percorre toda a lista de pacientes para gaurdá-los em ordem no documento
            if(paciente == NULL) {
                continue;
            }
            fprintf(f,"\n\t{\n");
            //Na triagem estamos apenas guardando o ID e na fila guardamos todas
            //as informações, assim o documento da triagme fica mais organizado.
            fprintf(f,"\t\t\"id\": %d",paciente_getid(paciente));
            fprintf(f,"\n\t}");
            //Verificação para no último elemento não ser colocada uma vírgula
            //após a inserção
            if(i<triagem->proximo-1){
                fprintf(f,",");
            }
        }
        fprintf(f, "\n");
    }
    fprintf(f, "]");
    fclose(f);
    return true;
}

void carregar_fila(TRIAGEM *triagem, LISTA_PACIENTE *lista){
    if(triagem != NULL){
        //Inicialização do ponteiro para leitura do arquivo
        FILE *f = fopen("fila.json", "r");
        if(f == NULL){
            return;
        }
        char buffer[101];
        int id;
        PACIENTE *paciente;
        //Percorre cada linha a procura do campo de id
        while( fgets(buffer,100,f) != NULL){
            if(strstr(buffer, "\"id\":")){
                //Uma vez encontrado o ID, o paciente é colocado na triagem
                //o paciente é acessado a partir da lista.
                sscanf(buffer,"%*[^:]: %d", &id);
                paciente = lista_paciente_buscar(lista, id);
                triagem_inserir_paciente(triagem, paciente);
            }
            paciente = NULL;
            free(paciente);
        }
        fclose(f);
    }
}