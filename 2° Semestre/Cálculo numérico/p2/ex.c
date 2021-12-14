#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float funcao(float x);
float derivada(float x);
float newton(float x_k);

int main(void) {

    float x_k1 = newton(-2);
    float x_k2 = newton(0);
    float x_k3 = newton(3);
    // Resposta final

    printf("As raizes de f(x) sao: %f %f e %f", x_k1, x_k2, x_k3);
}

float funcao(float x) {
    return pow(x,3)/2 - 5 * pow(x,2) /6 - 8 * x / 3 + 1;
}

float derivada(float x) {
    return 3 * pow(x,2) / 2 - 5 * x / 3  - 8 / 3;
}

float newton(float x_k) {
    float x_k1 = x_k;
    float f;
    float erro = INFINITY;
    int iteracao = 0;
    // Itera ate que o erro seja menor que o desejado
    while (erro >= 0.001) {
        // Atualiza os valores de x e f(x)
        x_k = x_k1;
        f = funcao(x_k);
        x_k1 = x_k - f / derivada(x_k);
        // Atualiza o valor do erro
        erro = fmin(fabs(x_k1 - x_k), fabs(f));
        iteracao++;
        // Prints da iteracao
        printf("\nIteracao: %d\n", iteracao);
        printf("\tErro: %f\n", erro);
        printf("\tx_%d: %f\n", iteracao, x_k1);
        printf("\tf(x_%d): %f\n", iteracao, f);
    }
    return x_k1;
}