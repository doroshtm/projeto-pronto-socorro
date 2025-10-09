#ifndef PACIENTE_H
    #define PACIENTE_H
    #include<stdbool.h>
    #include"historico.h"
    #include"lista_paciente.h"

    struct lista_paciente_;
    typedef struct lista_paciente_ LISTA_PACIENTE;

    typedef struct paciente_ PACIENTE;

    PACIENTE *paciente_criar(char nome[], LISTA_PACIENTE *, int id);
    bool paciente_apagar(PACIENTE **);
    int paciente_getid(PACIENTE *);
    char *paciente_getnome(PACIENTE *);
    HISTORICO *paciente_gethistorico(PACIENTE *);
    

#endif