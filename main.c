#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculadora.h"

int main() {

    system("cls");

    /* =====================================================
       Expressoes exatamente como na tabela do enunciado
       ===================================================== */

    struct {
        char *posFixa;
        char *inFixaRef;
        float esperado;
    } testes[] = {
        {"3 4 + 5 *",        "(3+4)*5",          35.0000f},
        {"7 2 * 4 +",        "7*2+4",             18.0000f},
        {"8 5 2 4 + * +",    "8+(5*(2+4))",       38.0000f},
        {"6 2 / 3 + 4 *",    "(6/2+3)*4",         24.0000f},
        {"9 5 2 8 * 4 + * +","9+(5*(4+8*2))",    109.0000f},
        {"2 3 + log 5 /",    "log(2+3)/5",         0.1398f},
        {"10 log 3 ^ 2 +",   "log(10)^3+2",        3.0000f},
        {"45 60 + 30 cos *", "(45+60)*cos(30)",   90.9327f},
        {"0.5 45 sen 2 ^ +", "0.5+sen(45)^2",      1.0000f}
    };

    int n = sizeof(testes) / sizeof(testes[0]);

    /* =====================================================
       TESTES - getValor
       ===================================================== */

    printf("============================================================\n");
    printf("                   TESTES - getValor                       \n");
    printf("============================================================\n");
    printf("%-5s %-26s %-10s %-10s %-8s\n",
           "Teste", "Pos-fixa", "Esperado", "Obtido", "Status");
    printf("------------------------------------------------------------\n");

    int pass_valor = 0;
    for (int i = 0; i < n; i++) {
        float obtido   = getValor(testes[i].posFixa);
        float esperado = testes[i].esperado;
        float diff     = obtido - esperado;
        if (diff < 0) diff = -diff;
        const char *status = (diff <= 0.001f) ? "OK" : "FALHOU";
        if (diff <= 0.001f) pass_valor++;

        printf("%-5d %-26s %-10.4f %-10.4f %-8s\n",
               i + 1,
               testes[i].posFixa,
               esperado,
               obtido,
               status);
    }

    printf("------------------------------------------------------------\n");
    printf("Resultado: %d/%d testes passaram\n\n", pass_valor, n);

    /* =====================================================
       TESTES - getInFixa
       ===================================================== */

    printf("============================================================\n");
    printf("                  TESTES - getInFixa                       \n");
    printf("============================================================\n");
    printf("%-5s %-26s %-24s %-24s\n",
           "Teste", "Pos-fixa", "Obtido", "Referencia");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        char *obtido = getInFixa(testes[i].posFixa);

        printf("%-5d %-26s %-24s %-24s\n",
               i + 1,
               testes[i].posFixa,
               obtido ? obtido : "NULL",
               testes[i].inFixaRef);
    }

    printf("------------------------------------------------------------\n");
    printf("Nota: compare visualmente — parentes extras sao aceitos\n");
    printf("      desde que a expressao seja matematicamente correta.\n\n");

    return 0;
}