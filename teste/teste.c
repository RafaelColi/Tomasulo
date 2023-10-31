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
    teste* t1;
    for(int i = 0; i < 2; i++) {
        char* id = (char*) calloc(4, sizeof(char));
        sprintf(id, "f%d", (i * 2));
        t1 = criar_teste(id);
    }

    testar_igualdade(t1, "f2");

    return 0;
}