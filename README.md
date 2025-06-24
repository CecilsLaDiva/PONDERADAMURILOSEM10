# Calculadora RPN (Notação Polonesa Reversa)

Este projeto implementa uma calculadora que avalia expressões matemáticas na notação RPN (Reverse Polish Notation), usando TAD Pilha em linguagem C.

## Como funciona

Na notação RPN:
- Os operandos vêm antes dos operadores
- A avaliação é feita usando uma pilha
- Exemplo: `(3 + 4) * 5` → `3 4 + 5 *`

## Como executar

1. Compile os arquivos:

```bash
gcc main.c pilha.c -o calculadora
