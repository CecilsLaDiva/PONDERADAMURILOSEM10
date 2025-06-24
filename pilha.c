#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, int valor) {
    if (p->topo < MAX - 1) {
        p->dados[++p->topo] = valor;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(1);
    }
}

int pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->dados[p->topo--];
    } else {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
}
