#ifndef PACIENTE_H
    #define PACIENTE_H
    #include<stdbool.h>
    #include"intencadeado.h"
    #include "historico.h"

    typedef struct paciente_ PACIENTE;

    PACIENTE *paciente_criar(char nome[100]);
    bool paciente_apagar(PACIENTE **);
    int paciente_getid(PACIENTE *);
    char *paciente_getnome(PACIENTE *);
    HISTORICO *paciente_gethistorico(PACIENTE *);
    

#endif