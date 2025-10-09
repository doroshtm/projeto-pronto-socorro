#ifndef LISTA_PACIENTE_H
    #define LISTA_PACIENTE_H
    #include"paciente.h"

    struct paciente_;
    typedef struct paciente_ PACIENTE;

    typedef struct lista_paciente_ LISTA_PACIENTE;

    LISTA_PACIENTE *lista_paciente_inicializar();
    bool lista_paciente_apagar(LISTA_PACIENTE **);
    bool lista_paciente_inserir(LISTA_PACIENTE *, PACIENTE *);
    int lista_paciente_gerar_id_unico(LISTA_PACIENTE *);
    bool lista_paciente_remover(LISTA_PACIENTE *, PACIENTE *);
    PACIENTE *lista_paciente_buscar(LISTA_PACIENTE *, int id);
    void lista_paciente_listar(LISTA_PACIENTE *);
    bool salvar_lista(LISTA_PACIENTE *);
    void carregar_lista(LISTA_PACIENTE *);

#endif
