#ifndef INTENCADEADO_H
    #define INTENCADEADO_H

    #include<stdbool.h>

    typedef struct intencadeado_ INTENCADEADO;

    bool intencadeado_inserir(int numero);
    bool intencadeado_apagarPrimeiro();
    INTENCADEADO *intencadeado_obterPrimeiro();
#endif