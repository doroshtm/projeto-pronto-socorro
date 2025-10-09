#include<stdio.h>
#include"triagem.h"
#include"paciente.h"
#include"historico.h"
#include"lista_paciente.h"

bool apagar_dados(LISTA_PACIENTE *lista_pacientes, TRIAGEM *triagem);

int main(void) {
    bool ok;
    LISTA_PACIENTE *lista_pacientes;
    lista_pacientes = lista_paciente_inicializar();
    carregar_lista(lista_pacientes);
    if (lista_pacientes == NULL) {
        printf("ERRO ao criar lista de pacientes!\n");
        return 1;
    }


    TRIAGEM *triagem;
    triagem = triagem_inicializar();
    carregar_fila(triagem, lista_pacientes);
    if(triagem == NULL){
        printf("Erro ao inicializar a triagem!");
        return 1;
    }

    printf("Bien venido manito!");
    int op = 0;
    do {
        // Escolhemos adicionar mais uma opção, "3-Inserir paciente na fila", para o caso de querermos inserir um paciente já cadastrado na lista, sem ter que mudar o funcionamento do TAD lista_paciente.
        printf("\nMenu:\n1-Registrar paciente\n2-Registrar óbito do paciente\n3-Inserir paciente na fila\n4-Adicionar procedimento ao histórico\n5-Desfazer procedimento do histórico\n6-Chamar paciente para atendimento\n7-Mostrar fila de espera\n8-Mostrar histórico do paciente\n9-Sair\n10-Limpar terminal(opcional)\n");
        printf("Digite a opção desejada: ");
        scanf("%d",&op);
        PACIENTE *paciente;
        int id;
        switch (op) {
            case 1:
                printf("------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                printf("Insira o nome do paciente: ");
                scanf("%s", nome);

                paciente = paciente_criar(nome, lista_pacientes, -1);
                if(paciente == NULL) {
                    printf("ERRO ao criar paciente!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }

                ok = lista_paciente_inserir(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao inserir paciente na lista de pacientes!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }

                id = paciente_getid(paciente);
                ok = triagem_inserir_paciente(triagem, paciente);
                if(!ok) {
                    printf("ERRO ao inserir paciente na triagem!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }

                printf("Paciente de ID %d registrado e inserido na fila de espera com sucesso!\n", id);
                printf("------------REGISTRO DE PACIENTE------------\n\n");
                break;
            case 2:
                printf("------------SISTEMA DE MORTE------------\n");
                
                printf("Id do paciente: ");
                scanf("%d",&id);
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                
                ok = lista_paciente_remover(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao remover paciente da lista de pacientes!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                
                ok = paciente_apagar(&paciente);
                if(!ok) {
                    printf("ERRO ao apagar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }

                printf("Paciente removido com sucesso!\n");
                printf("------------SISTEMA DE MORTE------------\n\n");

                break;
            case 3:
                printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n");
                printf("Essa função é para inserir um paciente já registrado no cadastro. Se acabou de registrar um paciente, ele já foi inserido na fila automaticamente. Insira -1 para voltar se for o caso.\n");
                printf("Id do paciente: ");
                scanf("%d",&id);
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                    break;
                }

                if(triagem_fila_cheia(triagem)) {
                    printf("ERRO ao inserir paciente na triagem: fila cheia!\n");
                    printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                    break;
                }

                ok = triagem_inserir_paciente(triagem, paciente);
                if(!ok) {
                    printf("ERRO ao inserir paciente na triagem!\n");
                    printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                    break;
                }
                printf("Paciente %s (ID %d) inserido na triagem com sucesso!\n", paciente_getnome(paciente), paciente_getid(paciente));
                printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                break;
            case 4:
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n");
                printf("Insira o id do paciente: ");
                scanf("%d",&id);
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                if(historico_cheio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao inserir procedimento: histórico cheio!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento: ");
                char procedimento[100];
                
                if(fscanf(stdin, " %99[^\n]", procedimento) != 1) {
                    printf("ERRO ao ler procedimento!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                if(!historico_inserir(paciente_gethistorico(paciente), procedimento)) {
                    printf("ERRO ao inserir histórico do paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento adicionado ao histórico do paciente!\n");
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                break;
            case 5:
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n");
                printf("Id do paciente: ");
                scanf("%d",&id);
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                if(historico_vazio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento: histórico vazio!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }

                if(!historico_retirar(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento do histórico do paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                
                printf("Procedimento desfeito do histórico do paciente!\n");
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                break;
            case 6:
                printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n");
                if(triagem_fila_vazia(triagem)) {
                    printf("ERRO ao chamar paciente: triagem vazia!\n");
                    printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n\n");
                    break;
                }

                paciente = triagem_remover_paciente(triagem);
                if(paciente == NULL) {
                    printf("ERRO ao remover paciente da triagem!\n");
                    printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n\n");
                    break;
                }

                printf("Paciente %s (ID %d) removido da triagem!\n", paciente_getnome(paciente), paciente_getid(paciente));
                
                printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n\n");
                break;
            case 7:
                printf("------------FILA DE ESPERA------------\n");
                triagem_mostrar_fila(triagem);
                printf("------------FILA DE ESPERA------------\n\n");
                break;
            case 8:
                printf("------------HISTÓRICO DO PACIENTE------------\n");
                printf("ID do paciente: ");
                scanf("%d",&id);
                paciente = lista_paciente_buscar(lista_pacientes,id);
                HISTORICO *historico = paciente_gethistorico(paciente);
                if(historico == NULL) {
                    printf("ERRO ao obter histórico de paciente!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                if(historico_vazio(historico)) {
                    printf("ERRO ao obter histórico de paciente: histórico vazio!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }

                char **procedimentos = malloc(10*sizeof(char *));
                if(procedimentos == NULL) {
                    printf("ERRO ao alocar memória para procedimentos!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                procedimentos = historico_consultar_procedimento(historico);
                if(procedimentos == NULL) {
                    printf("ERRO ao consultar procedimentos do histórico!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }

                int quantidade = historico_getquantidade(historico);
                for(int i = 0; i < quantidade; ++i) {
                    if(procedimentos[i] == NULL) {
                        break;
                    }
                    printf("Procedimento %d: %s\n",quantidade-i, procedimentos[i]);
                }
                printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                
                break;
            case 9:
            // sair (SALVAR)
                salvar_fila(triagem);
                salvar_lista(lista_pacientes);
                triagem_apagar(&triagem);
                lista_paciente_apagar(&lista_pacientes);
                break;
            default:
                break;
        }
    }while(op != 9);
}

bool apagar_dados(LISTA_PACIENTE *lista_pacientes, TRIAGEM *triagem) {
    bool ok, ok2;
    ok = lista_paciente_apagar(&lista_pacientes);
    ok2 = triagem_apagar(&triagem);

    return ok && ok2;
}