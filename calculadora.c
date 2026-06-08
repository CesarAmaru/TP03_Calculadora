#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <string.h>
#include "calculadora.h"
#define MXVP 128
#define PI 3.14159265358979323846
#define MXSTR 512

// Funções - getValor
typedef struct
{
    float lista[MXVP];
    int topo;
}Pilha;

static int Iniciar_P(Pilha *m){
    if (!m)
    {
        printf("\nNao ha Pilha.");
    }
    
    m->topo = -1;
}

static int Empilhar_P(Pilha *m, float valor){
    if (m->topo > MXVP){
        printf("\nFALHA em <Empilhar_P>!\n");
        return 0;
    }
    m->lista[++(m->topo)] = valor;
    return 1;
    
}

static int Desempilhar_P(Pilha *m, float *Valor){
    if (m->topo < 0)
    {
        printf("\nFALHA em <Desempilhar_P>!\n");
        return 0;
    }
    *Valor = m->lista[(m->topo)--];

    return 1;
}

//Funções - getValor
typedef struct 
{
    char dados[MXVP][MXSTR];
    char op[MXVP];
    int topo;
}Pilha_str;

static int Iniciar_str(Pilha_str *N) {
    if (!N) {
        printf("\nERRO em <Iniciar_str>!\n");
        return 0;
    }
    N->topo = -1;
    return 1;
}

static int Empilhar_str(Pilha_str *N, char *Str, char Op) {
    if (!N || !Str) {
        printf("\nERRO em <Empilhar_str>!\n");
        return 0;
    }
    strncpy(N->dados[++(N->topo)], Str, MXSTR - 1);
    N->dados[N->topo][MXSTR - 1] = '\0';
    N->op[N->topo] = Op;
    return 1;
}

static int Desempilhar_str(Pilha_str *N, char *Str_S, char *Op) {
    if (!N || !Str_S) {
        printf("\nERRO em <Desempilhar_str>!\n");
        return 0;
    }
    strncpy(Str_S, N->dados[(N->topo)], MXSTR - 1);
    Str_S[MXSTR - 1] = '\0';
    if (Op) *Op = N->op[N->topo];
    (N->topo)--;
    return 1;
}

static int Precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}


//Funções calculador.h
float getValor (char *Str){
    if (!Str)
    {
        printf("\nERRO em <getValor>\n");
        return 0;
    }
    
    Pilha p;
    Iniciar_P(&p);

    char buffer[MXSTR];
    strncpy(buffer, Str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *Sep = strtok(buffer, " ");
    while (Sep)
    {       
        char *final;
        float num = strtof(Sep, &final);
        if (final != Sep){
            Empilhar_P(&p, num);
        } else if (strlen(Sep) == 1)
        {
            float a, b;
            if (!Desempilhar_P(&p, &b) || !Desempilhar_P(&p, &a))
            {
                printf("\nFalha ao Desempilhar <getValor>!\n"); 
                return 0;
            }

            switch (Sep[0])
            {
                case '+':
                    Empilhar_P(&p, a+b);
                    break;
                case '-':
                    Empilhar_P(&p, a-b);
                    break;
                case '*':
                    Empilhar_P(&p, a*b);
                    break;
                case '/':
                    if (b == 0)
                    {
                        printf("\nNao eh possivel dividir por 0!!\n");
                        return 0;
                    }
                    Empilhar_P(&p, a/b);
                    break;
                case '%':
                    Empilhar_P(&p, fmod(a, b));
                    break;
                case '^':
                    Empilhar_P(&p, powf(a, b));
                    break;
                default:
                    printf("\nExpressao desconhecida!\n");
                    return 0;
            }
            
        } else{
            float a;
            if (!Desempilhar_P(&p, &a))
            {
                printf("\nFalha ao Desempilhar <getValor>!\n"); 
                return 0;
            }

            float radi = a * (PI / 180);
            if (strcmp(Sep, "sen") == 0) Empilhar_P(&p, sinf(radi));
            else if (strcmp(Sep, "cos") == 0) Empilhar_P(&p, cosf(radi));
            else if (strcmp(Sep, "tg") == 0) Empilhar_P(&p, tanf(radi));
            else if(strcmp (Sep, "raiz") == 0){
                if (a < 0)
                {
                    printf("\nRaiz de numero negativo. Erro em <getValor>\n"); 
                    return 0;
                }
                Empilhar_P(&p, sqrtf(a));
            }            
            else if(strcmp(Sep, "log") == 0){
                if (a <= 0)
                {
                    printf("\nFalha ao calcular log. Erro em <getValor>\n");
                    return 0;
                }
                Empilhar_P(&p, log10f(a));
            }
            else {
                printf("\nOperador desconhecido. Erro em <getValor>\n");
            }
            
        }
        
        Sep = strtok(NULL, " ");
    }
    float Result;
    if (!Desempilhar_P(&p, &Result))
    {
        printf("\nFalha ao captar resultado da operacao. Erro em <getValor>");
        return 0;
    }
    return Result;
}

char *getInFixa(char *Str) {
    if (!Str) {
        printf("\nERRO em <getInFixa>!\n");
        return NULL;
    }

    Pilha_str P;
    Iniciar_str(&P);

    char Buffer[MXSTR];
    strncpy(Buffer, Str, MXSTR - 1);
    Buffer[MXSTR - 1] = '\0';
    char bTemp[MXSTR];

    char *Sep = strtok(Buffer, " ");

    while (Sep) {
        char *final;
        strtof(Sep, &final);

        if (final != Sep) {
            if (!Empilhar_str(&P, Sep, '\0')) {
                printf("\nERRO em <getInFixa>!\n");
                return NULL;
            }

        } else if (strlen(Sep) == 1) {

            char a[MXSTR], b[MXSTR];
            char op_a, op_b;
            char op = Sep[0];

            if (!Desempilhar_str(&P, b, &op_b) || !Desempilhar_str(&P, a, &op_a)) {
                printf("\nERRO em <getInFixa>!\n");
                return NULL;
            }

            int wrap_a = (op_a != '\0' && Precedencia(op_a) < Precedencia(op));
            int wrap_b = (op_b != '\0') && (
                            Precedencia(op_b) < Precedencia(op) ||
                            (Precedencia(op_b) == Precedencia(op) &&
                             (op == '-' || op == '/' || op == '^'))
                         );

            snprintf(bTemp, MXSTR, "%s%s%s%c%s%s%s",
                     wrap_a ? "(" : "", a, wrap_a ? ")" : "",
                     op,
                     wrap_b ? "(" : "", b, wrap_b ? ")" : "");

            if (!Empilhar_str(&P, bTemp, op)) {
                printf("\nERRO em <getInFixa>!\n");
                return NULL;
            }

        } else {
            char a[MXSTR];
            if (!Desempilhar_str(&P, a, NULL)) {
                printf("\nERRO em <getInFixa>!\n");
                return NULL;
            }

            snprintf(bTemp, MXSTR, "%s(%s)", Sep, a);

            if (!Empilhar_str(&P, bTemp, '\0')) {
                printf("\nERRO em <getInFixa>!\n");
                return NULL;
            }
        }

        Sep = strtok(NULL, " ");
    }

    static char Expressao[MXSTR];
    if (!Desempilhar_str(&P, Expressao, NULL)) {
        printf("\nERRO em <getInFixa>!\n");
        return NULL;
    }
    return Expressao;
}