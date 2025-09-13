#include"intencadeado.h"
#include<stdlib.h>

struct intencadeado_ {
    int numero;
    INTENCADEADO *proximoInt;
    INTENCADEADO *anteriorInt;
};

INTENCADEADO *primeiroInt;
INTENCADEADO *ultimoInt;

// essa lista encadeada funciona por meio de FIFO

bool intencadeado_inserir(int numero) {
    INTENCADEADO *novoInt = malloc(sizeof(INTENCADEADO));

    if (novoInt == NULL) {
        return false;
    }
    
    novoInt->numero = numero;
    novoInt->proximoInt = NULL;
    ultimoInt->proximoInt = novoInt;
    ultimoInt = novoInt;
    
    return true;
}

bool intencadeado_apagarPrimeiro() {
    if (primeiroInt == NULL) {
        return false;
    }
    INTENCADEADO *temp = primeiroInt;
    primeiroInt = primeiroInt->proximoInt;
    if(primeiroInt == NULL) {
        // Caso a lista fique vazia, atualizamos o último elemento
        ultimoInt = NULL;
    } else {
        primeiroInt->anteriorInt = NULL;       
    }

    free(temp);

    return true;
}

INTENCADEADO *intencadeado_obterPrimeiro() {
    return primeiroInt;
}