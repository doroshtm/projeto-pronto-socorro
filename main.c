#include<stdio.h>
#include"triagem.h"
#include"io.h"
#include"lista_paciente.h"

bool apagar_dados(LISTA_PACIENTE *lista_pacientes, TRIAGEM *triagem);

int main(void) {
    bool ok;
    TRIAGEM *triagem;
    triagem = triagem_inicializar();
    if(triagem == NULL){
        printf("Erro ao inicializar a triagem!");
        return 1;
    }

    LISTA_PACIENTE *lista_pacientes;
    lista_pacientes = lista_paciente_inicializar();

    if (lista_pacientes == NULL) {
        printf("ERRO ao criar lista de pacientes!\n");
        return 1;
    }

    printf("Bien venido manito!");
    int op = 0;
    do {
        printf("\nMenu:\n1-Registrar paciente\n2-Dar alta ao paciente\n3-Adicionar procedimento ao histórico\n4-Desfazer procedimento do histórico\n5-Chamar paciente para atendimento\n6-Mostrar fila de espera\n7-Mostrar histórico do paciente\n8-Sair\n9-Limpar terminal(opcional)\n");
        printf("Digite a action desejada: ");
        scanf("%d",&op);
        switch (op) {
            case 1:
                printf("------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                printf("Insira o nome do paciente: ");
                scanf("%s", nome);

                PACIENTE *paciente = paciente_criar(nome);
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

                int id = paciente_getid(paciente);
                ok = triagem_inserir_paciente(triagem, id);
                if(!ok) {
                    printf("ERRO ao inserir paciente na triagem!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }

                printf("Paciente de ID %d inserido com sucesso!", id);
                printf("------------REGISTRO DE PACIENTE------------\n\n");
                break;
            case 2:
                printf("------------SISTEMA DE MORTE------------\n");
                // remover paciente da lista de pacientes
                // CHECAR SE NÃO ESTÁ NA TRIAGEM
                printf("Id do paciente: ");
                int id;
                scanf("%d", &id);
                PACIENTE *paciente = paciente_buscar(id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                // verificar se o paciente está na triagem? Apenas remover da triagem?
                
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
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n");
                printf("Insira o id do paciente: ");
                int id;
                scanf("%d",&id);
                PACIENTE *paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento: ");
                char procedimento[100];
                if(sscanf(stdin, "%99s", procedimento) != 1) {
                    printf("ERRO ao ler procedimento!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                if(!historico_inserir(paciente_gethistorico(paciente), procedimento)) {
                    printf("ERRO ao inserir histórico do paciente!");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento adicionado ao histórico do paciente!\n");
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                break;
            case 4:
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n");
                printf("Id do paciente: ");
                int id;
                scanf("%d",&id);
                PACIENTE *paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                if(!historico_retirar(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento do histórico do paciente!");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                
                printf("Procedimento desfeito do histórico do paciente!\n");
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                break;
            case 5:
                printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n");
                PACIENTE *paciente;
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
            case 6:
                printf("------------FILA DE ESPERA------------\n");
                triagem_mostrar_fila(triagem, lista_pacientes);
                printf("------------FILA DE ESPERA------------\n\n");
                break;
            case 7:
                printf("------------HISTÓRICO DO PACIENTE------------\n");
                printf("ID do paciente: ");
                int id;
                scanf("%d", &id);
                HISTORICO *historico = historico_consultar(id);
                if(historico == NULL) {
                    printf("ERRO ao obter histórico de paciente!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }

                char *procedimentos[10] = historico_consultar_procedimento(historico);

                for(int i = 0; i < 10; ++i) {
                    printf("Procedimento %d: %s\n",10-i,procedimentos[i]);
                }
                printf("------------HISTÓRICO DO PACIENTE------------\n\n");

                
                break;
            case 8:
            // sair (SALVAR)
                
                if(!apagar_dados(lista_pacientes, triagem)) {
                    printf("ERRO ao apagar dados em memória!\n");
                    // break;
                }

                salvar_dados(paciente, historico);
                break;
            default:
                break;
        }
    }while(op != 8);
}

bool apagar_dados(LISTA_PACIENTE *lista_pacientes, TRIAGEM *triagem) {
    bool ok, ok2;
    ok = lista_paciente_apagar(&lista_pacientes);
    ok2 = triagem_apagar(&triagem);

    return ok && ok2;
}