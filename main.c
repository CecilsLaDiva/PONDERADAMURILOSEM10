#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pilha.h"

int ehNumero(char *token) {
    for (int i = 0; token[i]; i++) {
        if (!isdigit(token[i]) && !(i == 0 && token[i] == '-')) return 0;
    }
    return 1;
}

int main() {
    char expressao[256];
    Pilha pilha;
    inicializaPilha(&pilha);

    printf("Digite uma expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin);

    char *token = strtok(expressao, " \n");
    while (token != NULL) {
        if (ehNumero(token)) {
            push(&pilha, atoi(token));
        } else {
            int b = pop(&pilha);
            int a = pop(&pilha);
            int resultado = 0;

            if (strcmp(token, "+") == 0)
                resultado = a + b;
            else if (strcmp(token, "-") == 0)
                resultado = a - b;
            else if (strcmp(token, "*") == 0)
                resultado = a * b;
            else if (strcmp(token, "/") == 0)
                resultado = a / b;
            else {
                printf("Operador inválido: %s\n", token);
                return 1;
            }

            push(&pilha, resultado);
        }

        token = strtok(NULL, " \n");
    }

    printf("Resultado: %d\n", pop(&pilha));
    return 0;
}
