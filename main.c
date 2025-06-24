#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 1000


typedef struct {
    double dados[MAX_STACK_SIZE];
    int topo;
} Pilha;


void inicializaPilha(Pilha *p) {
    p->topo = -1;
}


int estaVazia(Pilha *p) {
    return p->topo == -1;
}


int estaCheia(Pilha *p) {
    return p->topo == MAX_STACK_SIZE - 1;
}


void push(Pilha *p, double valor) {
    if (estaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
        exit(1);
    }
    p->dados[++p->topo] = valor;
}


double pop(Pilha *p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->dados[p->topo--];
}


double topo(Pilha *p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->dados[p->topo];
}


int ehNumero(char *token) {
    int i = 0;

    if (token[0] == '-' || token[0] == '+') {
        i = 1;
    }

    if (token[i] == '\0') {
        return 0;
    }

    int temPonto = 0;


    while (token[i] != '\0') {
        if (token[i] == '.') {
            if (temPonto) return 0;
            temPonto = 1;
        } else if (!isdigit(token[i])) {
            return 0; 
        }
        i++;
    }

    return 1;
}


int ehOperador(char *token) {
    return strlen(token) == 1 && 
           (token[0] == '+' || token[0] == '-' || 
            token[0] == '*' || token[0] == '/');
}

double aplicarOperacao(double a, double b, char operador) {
    switch (operador) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Erro: Divisão por zero!\n");
                exit(1);
            }
            return a / b;
        default:
            printf("Erro: Operador inválido '%c'\n", operador);
            exit(1);
    }
}


void imprimirPilha(Pilha *p) {
    printf("Pilha: [");
    for (int i = 0; i <= p->topo; i++) {
        printf("%.2f", p->dados[i]);
        if (i < p->topo) printf(", ");
    }
    printf("]\n");
}

double avaliarRPN(char *expressao) {
    Pilha pilha;
    inicializaPilha(&pilha);

    char *token = strtok(expressao, " \t\n");

    printf("=== Avaliação passo a passo ===\n");

    while (token != NULL) {
        printf("Token: '%s' -> ", token);

        if (ehNumero(token)) {
            double numero = atof(token);
            push(&pilha, numero);
            printf("push(%.2f)", numero);
        }
        else if (ehOperador(token)) {

            if (pilha.topo < 1) {
                printf("\nErro: Operandos insuficientes para '%s'\n", token);
                exit(1);
            }

            double b = pop(&pilha);
            double a = pop(&pilha);
            double resultado = aplicarOperacao(a, b, token[0]);

            push(&pilha, resultado);
            printf("pop(%.2f), pop(%.2f) -> %.2f %c %.2f = %.2f -> push(%.2f)", 
                   b, a, a, token[0], b, resultado, resultado);
        }
        else {
            printf("\nErro: Token inválido '%s'\n", token);
            exit(1);
        }

        printf(" | ");
        imprimirPilha(&pilha);

        token = strtok(NULL, " \t\n");
    }

    if (pilha.topo != 0) {
        printf("\nErro: Expressão mal formada - pilha deveria ter apenas um elemento\n");
        printf("Elementos restantes na pilha: %d\n", pilha.topo + 1);
        exit(1);
    }

    return topo(&pilha);
}


int main() {
    char expressao[MAX_INPUT_SIZE];

    printf("=== CALCULADORA RPN ===\n");
    printf("Digite uma expressão em notação polonesa reversa:\n");
    printf("Exemplo: 3 4 + 5 *\n");
    printf("Operadores suportados: + - * /\n");
    printf("Digite 'sair' para encerrar\n\n");

    while (1) {
        printf("RPN> ");

        if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
            break;
        }

        expressao[strcspn(expressao, "\n")] = '\0';

        if (strcmp(expressao, "sair") == 0 || strcmp(expressao, "exit") == 0) {
            break;
        }

        if (strlen(expressao) == 0) {
            continue;
        }


        char expressaoCopia[MAX_INPUT_SIZE];
        strcpy(expressaoCopia, expressao);

        double resultado = avaliarRPN(expressaoCopia);
        printf("\n=== RESULTADO FINAL: %.6g ===\n\n", resultado);
    }

    printf("Calculadora encerrada.\n");
    return 0;
}


void executarTestes() {
    printf("=== EXECUTANDO TESTES ===\n\n");

    char testes[][50] = {
        "3 4 +",           // 7
        "5 1 2 + 4 * + 3 -", // 14
        "15 7 1 1 + - / 3 * 2 1 1 + + -", // 5
        "4 2 + 3 5 1 - * +", // 18
        "3 4 * 2 +",       // 14
        "10 2 /",          // 5
        "1 2 + 3 4 + *"    // 21
    };

    double resultadosEsperados[] = {7, 14, 5, 18, 14, 5, 21};

    int numTestes = sizeof(testes) / sizeof(testes[0]);

    for (int i = 0; i < numTestes; i++) {
        printf("Teste %d: %s\n", i + 1, testes[i]);

        char expressaoCopia[50];
        strcpy(expressaoCopia, testes[i]);

        double resultado = avaliarRPN(expressaoCopia);
        printf("Resultado: %.6g | Esperado: %.6g", resultado, resultadosEsperados[i]);

        if (resultado == resultadosEsperados[i]) {
            printf(" ✓ PASSOU\n");
        } else {
            printf(" ✗ FALHOU\n");
        }

        printf("\n");
    }
}