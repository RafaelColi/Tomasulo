#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct teste {
    char* nome;
} teste;

teste* criar_teste(char* nome) {
    teste* new = (teste*) calloc(1, sizeof(teste));

    new->nome = nome;

    return new;
}

void testar_igualdade(teste* teste, char* nome) {
    if(!strcmp(teste->nome, nome)) {
        printf("Strings iguais\n");
    } else {
        printf("Strings diferentes\n");
    }

    return;
}

int main() {
    teste* t1 = criar_teste("rafael");
    char* nome = "rafael";
    testar_igualdade(t1, nome);

    return 0;
}