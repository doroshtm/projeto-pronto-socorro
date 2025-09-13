#ifndef TRIAGEM_H
    #define TRIAGEM_H

    #include"paciente.h"
    #include"lista_paciente.h"

    typedef struct triagem_ TRIAGEM;

    TRIAGEM *triagem_inicializar();
    bool triagem_inserir_paciente(TRIAGEM *, PACIENTE *);
    PACIENTE *triagem_remover_paciente(TRIAGEM *);
    bool triagem_fila_cheia(TRIAGEM *);
    bool triagem_fila_vazia(TRIAGEM *);
    void triagem_mostrar_fila(TRIAGEM *, LISTA_PACIENTE *);
    bool triagem_apagar(TRIAGEM **);

#endif