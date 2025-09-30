#ifndef IO_H
    #define IO_H

    #include "paciente.h"
    #include "triagem.h"
    #include "lista_paciente.h"

    void carregar_dados(LISTA_PACIENTE *lista, TRIAGEM *triagem);
    bool salvar_dados(PACIENTE *lista, TRIAGEM *triagem);

#endif