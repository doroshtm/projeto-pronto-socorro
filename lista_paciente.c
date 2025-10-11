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

//Criação da lisat de pacientes
LISTA_PACIENTE *lista_paciente_inicializar() {
    //Alocação da lista de paciente
    LISTA_PACIENTE *novaLista = malloc(sizeof(LISTA_PACIENTE));
    if(novaLista == NULL) {
        return NULL;
    }
    //No início, sem pacientes, temos o primeiro e último itens sendo ponteiros nulos
    novaLista->primeiro = NULL;
    novaLista->ultimo = NULL;
    return novaLista;
}

//Função para inserir paciente na lista
bool lista_paciente_inserir(LISTA_PACIENTE *lista, PACIENTE *paciente) {
    if(paciente == NULL) {
        return false;
    }
    //Aloca novo nó
    NO *novoNo = malloc(sizeof(NO));
    if(novoNo == NULL) {
        return false;
    }
    //Guarda o paciente na lista
    novoNo->paciente = paciente;
    //Como o nó é colocado ao final por ser uma lista o próximo do último
    //sempre será nulo
    novoNo->proximo = NULL;
    if(lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    } else {
        lista->ultimo->proximo = novoNo;
    }
    
    lista->ultimo = novoNo;

    return true;
}

//Função para remover pacienete da lista
bool lista_paciente_remover(LISTA_PACIENTE *lista, PACIENTE *paciente) {
    if(lista == NULL || paciente == NULL) {
        return false;
    }

    //Uso de 2 ponteiros para poder apagar o elemento da lista
    NO *atual = lista->primeiro;
    NO *anterior = NULL;

    //Quando o ponteiro atual encontrar, o anterior que aponta para o anterior
    //dessa forma o anterior pode apontar para o próximo do atual e depois o atual
    //Pode ser apagado
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

//Função para buscar paciente
PACIENTE *lista_paciente_buscar(LISTA_PACIENTE *lista, int id) {
    if(lista == NULL || id < 0) {
        return NULL;
    }

    NO *atual = lista->primeiro;
    //Percorre toda a lista até encontrar o id certo ou acabar a lista
    while(atual != NULL) {
        if(paciente_getid(atual->paciente) == id) {
            return atual->paciente;
        }
        atual = atual->proximo;
    }
    //Caso a lista acabe é retornado um ponteiro nulo
    return NULL;
}

//Função para mostrar a lista de pacientes
void lista_paciente_listar(LISTA_PACIENTE *lista) {
    //Por ser uma lista encadeada
    //Cada nó deve ser percorrido individualmente
    NO *atual = lista->primeiro;

    if(atual == NULL || atual->paciente == NULL) {
        printf("Não há nenhum paciente!");
        return;
    }
    //O i foi utilizado para melhor acompanhamento das posições na lista
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

//Função para gerar um id único de cada paciente
//Melhor para busca e remoção de valores únicos
//Para evitar repetição um identificador é sempre 1 a mais que seu anterior
int lista_paciente_gerar_id_unico(LISTA_PACIENTE *lista) {
    return lista->ultimo == NULL ? 0 : paciente_getid(lista->ultimo->paciente) + 1;
}

//Apagar a lista de pacientes
bool lista_paciente_apagar(LISTA_PACIENTE **lista) {
    if(lista == NULL || *lista == NULL) {
        return false;
    }

    NO *atual = (*lista)->primeiro;
    NO *proximo;

    //Na lista é necessário apagar cada paciente individualmente para depois
    //Apagar o ponteiro para a lista
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

//Função para salvar os dados da lista
bool salvar_lista(LISTA_PACIENTE *lista){

    //Inicialização do ponteiro para escrita do arquivo
    FILE *f = fopen("lista.json", "w");
    if(f == NULL){
        return false;
    }
    //Como é uma lista encadeada cada nó deverá ser percorrido na memória
    //para um correto salvamento dos dados
    NO *atual = lista->primeiro;
    //Início do arquivo seguindo o formato JSON
    fprintf(f, "[");
    if(atual != NULL && atual->paciente != NULL) {
        while(atual != NULL) {
            fprintf(f,"\n\t{");
            fprintf(f,"\n\t\t\"id\": %d,\n", paciente_getid(atual->paciente));
            fprintf(f,"\t\t\"nome\": \"%s\",\n", paciente_getnome(atual->paciente));
            //Ao chegar no histórico cada procedimento deverá ser salvado na lista
            //A ordem da pilha se manterá no salvamento
            fprintf(f,"\t\t\"histórico\": {");
            PROCEDIMENTO *procedimento = historico_getultimo(paciente_gethistorico(atual->paciente));
            //A cada atualização do nó atual o histórico se altera, assim
            //É possível manter o número mínimo de loops de acordo com cada paciente.
            for(int j=0; j< historico_getquantidade(paciente_gethistorico(atual->paciente)); j++){
                if(j==0){
                    fprintf(f, "\n");
                }
                fprintf(f, "\t\t\t\"procedimento\": \"%s\"", procedimento_gettexto(procedimento));
                if(j < historico_getquantidade(paciente_gethistorico(atual->paciente))-1){
                    fprintf(f,",");
                }
                fprintf(f, "\n");
                procedimento = procedimento_getanterior(procedimento);
                if(j == historico_getquantidade(paciente_gethistorico(atual->paciente))-1){
                    fprintf(f, "\t\t");
                }
            }
            fprintf(f,"}\n");
            atual = atual->proximo;
            fprintf(f, "\t}");
            if(atual != NULL){
                fprintf(f, ",");
            }
        }
        fprintf(f, "\n");
    }
    fprintf(f, "]");
    fclose(f);
    return true;
}

//Função para carregar dados da lista de pacientes
void carregar_lista(LISTA_PACIENTE *lista){
    if(lista!=NULL){
        //Inincialização do ponteiro para leitura do arquivo
        FILE *f = fopen("lista.json", "r");
        if(f == NULL){
            return;
        }
        char buffer[101], nome[101], procedimento[11];
        int id;
        PACIENTE *paciente;
        //Enquanto houver conteúdo no documento ele lê cada linha e verifica se
        //na linha algum dos campos procurados é encontrado e vai armazenando os dados
        //até atingir o campo histórico(último campo de cada registro)
        while(fgets(buffer, 100, f) != NULL){
            if(strstr(buffer, "\"id\":")){
                sscanf(buffer, "%*[^:]: %d", &id);
            }else if(strstr(buffer, "\"nome\":")){
                sscanf(buffer, "%*[^:]: \"%[^\"]", nome);
                paciente = paciente_criar(nome, lista, id);
            }else if(strstr(buffer, "\"histórico\":")){
                //Percorre o histórico até que o campo acabe e pega seus dados
                while(fgets(buffer, 100, f) != NULL && !strstr(buffer, "}")){
                    if(strstr(buffer, "\"procedimento\":")){
                        sscanf(buffer, "%*[^:]: \"%[^\"]", procedimento);
                        historico_inserir(paciente_gethistorico(paciente), procedimento);
                    }
                }
                //Como historico é uma lista, ao pegar os dados a lista é invertida na pilha
                //Para isso é necessárioinvertê-la novamente
                historico_inverter(paciente_gethistorico(paciente));
                //O paciente é inserido na lista
                lista_paciente_inserir(lista, paciente);
                paciente = NULL;
                free(paciente);
            }
        }
        fclose(f);
    }
}