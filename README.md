# Calculadora RPN

## O que é RPN?
Notação Polonesa Reversa - é quando em um "cálculo" o operador vem depois dos números.
- Exemplo: `3 4 +` = 7 (em vez de `3 + 4`)

## Como Usar
1. Rode o programa
2. Digite as expressões RPN separadas por espaço
3. Pressione Enter
4. Digite "sair" para parar

## Exemplos
```
3 4 +           → 7
5 1 2 + 4 * + 3 -   → 14  
10 2 /          → 5
```

## Como Funciona
1. **Pilha**: Usa uma pilha para guardar números
2. **Algoritmo**: 
   - Se é número: empilha
   - Se é operador (+, -, *, /): desempilha 2 números, calcula, empilha resultado
3. **Resultado**: O que sobra na pilha