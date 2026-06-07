#include <stdio.h>
#include "calculadora.h"

int main() {
    Expressao testes[] = {
        {"3 4 + 5 *",          "",  35.0f},
        {"7 2 * 4 +",          "",  18.0f},
        {"8 5 2 4 + * +", "", 38.0f},
        {"6 2 / 3 + 4 *",      "",  24.0f},
        {"9 5 4 8 2 * + * +", "", 109.0f},
        {"2 3 + log 5 /",      "",   0.14f},
        {"10 log 3 ^ 2 +",     "",   3.0f},
        {"45 60 + 30 cos *", "", 90.93f},
        {"0.5 45 sen 2 ^ +",   "",   1.0f}
    };

    int n = sizeof(testes) / sizeof(testes[0]);

    printf("%-5s %-25s %-10s %-10s %-10s\n",
           "Teste", "Expressao", "Esperado", "Obtido", "Status");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        float obtido   = getValor(testes[i].posFixa);
        float esperado = testes[i].Valor;
        float diff     = obtido - esperado;
        if (diff < 0) diff = -diff;  /* valor absoluto sem math.h */

        /* tolerância de 0.001 conforme o enunciado */
        const char *status = (diff <= 0.001f) ? "OK" : "FALHOU";

        printf("%-5d %-25s %-10.4f %-10.4f %-10s\n",
               i + 1,
               testes[i].posFixa,
               esperado,
               obtido,
               status);
    }

    return 0;
}