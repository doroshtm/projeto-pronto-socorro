//Arthur de Castro Dias - 16855302
//Gabriel Carraro Salzedas - 16827905
//Kaua Benjamin Trombim Silva - 16830893
#include<stdio.h>
#include"triagem.h"
#include"paciente.h"
#include"historico.h"
#include"lista_paciente.h"

int main(void) {
    bool ok;
    //A lista é inicializada e os dados são carregados
    LISTA_PACIENTE *lista_pacientes;
    lista_pacientes = lista_paciente_inicializar();
    carregar_lista(lista_pacientes);
    if (lista_pacientes == NULL) {
        printf("ERRO ao criar lista de pacientes!\n");
        return 1;
    }

    //Inicialização e carregamento da triagem
    //Necessário depois da lista pois seu carregamento depende dela
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
        printf("\nMenu:\n1-Registrar paciente\n2-Registrar óbito do paciente\n3-Inserir paciente na fila\n4-Adicionar procedimento ao histórico\n5-Desfazer procedimento do histórico\n6-Chamar paciente para atendimento\n7-Mostrar fila de espera\n8-Mostrar histórico do paciente\n9-Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d",&op);
        PACIENTE *paciente;
        int id;
        //Executa alguma das ações de aocrdo com a entrada do usuário
        switch (op) {
            case 1:
                //Registrar paciente
                printf("------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                printf("Insira o nome do paciente: ");
                scanf("%s", nome);
                //Cria paciente com o nome dado, id -1 para identificação de que
                //ele é um novo paciente
                paciente = paciente_criar(nome, lista_pacientes, -1);
                if(paciente == NULL) {
                    printf("ERRO ao criar paciente!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }
                //Paciente é guardado na lista geral
                ok = lista_paciente_inserir(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao inserir paciente na lista de pacientes!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }
                //Paciente é inserido na fila de triagem para ser atendido
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
            //Óbito do paciente
                printf("------------SISTEMA DE MORTE------------\n");
                
                printf("Id do paciente: ");
                scanf("%d",&id);
                //Busca do paciente na lista para sua remoção
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                //Remoção do paciente da lista
                ok = lista_paciente_remover(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao remover paciente da lista de pacientes!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                //Apagar paciente para liberar memória para novo paciente
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
            //Inserção de paciente na fila
                printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n");
                printf("Essa função é para inserir um paciente já registrado no cadastro. Se acabou de registrar um paciente, ele já foi inserido na fila automaticamente. Insira -1 para voltar se for o caso.\n");
                printf("Id do paciente: ");
                scanf("%d",&id);
                //Busca paciente na lista, se for -1 nãoo encontra e sai da função
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                    break;
                }
                //Aviso caso a triagem esteja cheia
                if(triagem_fila_cheia(triagem)) {
                    printf("ERRO ao inserir paciente na triagem: fila cheia!\n");
                    printf("------------INSERÇÃO DE PACIENTE NA FILA------------\n\n");
                    break;
                }
                //Paciente é colocado na fila
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
                //Registro de procedimento ao histórico
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n");
                printf("Insira o id do paciente: ");
                scanf("%d",&id);
                //Busca pelo paciente
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }
                //Se o histórico do paciente estiver cheio o usuário recebe um aviso
                if(historico_cheio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao inserir procedimento: histórico cheio!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento: ");
                char procedimento[100];
                //Lê o procedimento do usuário
                if(fscanf(stdin, " %99[^\n]", procedimento) != 1) {
                    printf("ERRO ao ler procedimento!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }
                //Avisa se houver erro na inserção
                if(!historico_inserir(paciente_gethistorico(paciente), procedimento)) {
                    printf("ERRO ao inserir histórico do paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento adicionado ao histórico do paciente!\n");
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                break;
            case 5:
                //O último procedimento do histórioc é desfeito
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n");
                printf("Id do paciente: ");
                scanf("%d",&id);
                //Procura o paciente que terá o histórico alterado
                paciente = lista_paciente_buscar(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                //Se o histórico estiver vazio não tem como retirar nada
                if(historico_vazio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento: histórico vazio!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                //Se falhar avisa ao usuário
                if(!historico_retirar(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento do histórico do paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                
                printf("Procedimento desfeito do histórico do paciente!\n");
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                break;
            case 6:
                //Paciente é chamado para atendimento
                printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n");
                //Se não houver pacinetes não há quem chamar
                if(triagem_fila_vazia(triagem)) {
                    printf("ERRO ao chamar paciente: triagem vazia!\n");
                    printf("------------CHAMAR PACIENTE PARA ATENDIMENTO------------\n\n");
                    break;
                }
                //Guarda o primeiro paciente da fila e o remove da fila
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
                //Mostra a triagem e os pacientes nela
                printf("------------FILA DE ESPERA------------\n");
                triagem_mostrar_fila(triagem);
                printf("------------FILA DE ESPERA------------\n\n");
                break;
            case 8:
                //Mostra o histórico do paciente
                printf("------------HISTÓRICO DO PACIENTE------------\n");
                printf("ID do paciente: ");
                scanf("%d",&id);
                //Procura pelo apciente na lista
                paciente = lista_paciente_buscar(lista_pacientes,id);
                HISTORICO *historico = paciente_gethistorico(paciente);
                if(historico == NULL) {
                    printf("ERRO ao obter histórico de paciente!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                //Verifica se o histórico não está vazio
                if(historico_vazio(historico)) {
                    printf("ERRO ao obter histórico de paciente: histórico vazio!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                //Guarda um vetor de strings com os procedimentos
                char **procedimentos = malloc(10*sizeof(char *));
                if(procedimentos == NULL) {
                    printf("ERRO ao alocar memória para procedimentos!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                //recebe todos os procedimentos
                procedimentos = historico_consultar_procedimento(historico);
                if(procedimentos == NULL) {
                    printf("ERRO ao consultar procedimentos do histórico!\n");
                    printf("------------HISTÓRICO DO PACIENTE------------\n\n");
                    break;
                }
                //Printa os procedimentos de acordo com a quantidade no histórico
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
            // Sair do loop e salvamento dos dados
                //A fila e a lista são salvas
                salvar_fila(triagem);
                salvar_lista(lista_pacientes);
                //Após seu salvamento a triagem e a lista de pacientes são apagadas
                triagem_apagar(&triagem);
                lista_paciente_apagar(&lista_pacientes);
                break;
            default:
            //Caso a opção digitada seja inválida nada acontece
                break;
        }
    }while(op != 9);
}