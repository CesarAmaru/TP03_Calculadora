#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calculadora.h"
#define MXVP 100
#define PI 3.14159265358979323846

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
        printf("\nFALHA em <Empilhar_P>!");
        return 0;
    }
    m->lista[++(m->topo)] = valor;
    return 1;
    
}
static int Desempilhar_P(Pilha *m, float *Valor){
    if (m->topo < 0)
    {
        printf("\nFALHA em <Desempilhar_P>!");
        return 0;
    }
    *Valor = m->lista[(m->topo)--];

    return 1;
}


//Funções calculador.h
float getValor (char *Str){
    Pilha p;
    Iniciar_P(&p);

    char buffer[256];
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
                printf("\nFalha ao Desempilhar <getValor>!"); 
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
                        printf("\nNao eh possivel dividir por 0!!");
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
                    printf("\nExpressao desconhecida!");
                    return 0;
            }
            
        } else{
            float a;
            if (!Desempilhar_P(&p, &a))
            {
                printf("\nFalha ao Desempilhar <getValor>!"); 
                return 0;
            }

            float radi = a * (PI / 180);
            if (strcmp(Sep, "sen") == 0) Empilhar_P(&p, sinf(radi));
            else if (strcmp(Sep, "cos") == 0) Empilhar_P(&p, cosf(radi));
            else if (strcmp(Sep, "tg") == 0) Empilhar_P(&p, tanf(radi));
            else if(strcmp (Sep, "raiz") == 0){
                if (a < 0)
                {
                    printf("\nRaiz de numero negativo. Erro em <getValor>"); 
                    return 0;
                }
                Empilhar_P(&p, sqrtf(a));
            }            
            else if(strcmp(Sep, "log") == 0){
                if (a <= 0)
                {
                    printf("\nFalha ao calcular log. Erro em <getValor>");
                    return 0;
                }
                Empilhar_P(&p, log10f(a));
            }
            else {
                printf("\nOperador desconhecido. Erro em <getValor>");
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