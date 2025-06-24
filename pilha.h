#ifndef PILHA_H
#define PILHA_H

#define MAX 100

typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

void inicializaPilha(Pilha *p);
int estaVazia(Pilha *p);
void push(Pilha *p, int valor);
int pop(Pilha *p);

#endif
