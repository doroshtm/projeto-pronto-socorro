#ifndef HISTORICO_H
    #define HISTORICO_H
    #include<stdbool.h>
    #include<stdlib.h>

    typedef struct historico_ HISTORICO;

    HISTORICO *historico_criar();
    bool historico_apagar(HISTORICO **);
    bool historico_inserir(HISTORICO *, char *);
    bool historico_retirar(HISTORICO *);
    bool historico_cheio(HISTORICO *);
    bool historico_vazio(HISTORICO *);

#endif