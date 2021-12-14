#include <stdio.h>

void bubblesort (int vetor[], int n);

int main(void) {
	int vetor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int vet_len = sizeof(vetor) / sizeof(vetor[0]);
    float mediana;
	
    // Primeiro ordeno o vetor em ordem crescente
    bubblesort(vetor, vet_len);

    // Em seguida encontro a media dos dois valores do meio
    // Ou apenas o valor do meio
    if(vet_len % 2){
        mediana = vetor[vet_len / 2];
    } else {
        mediana = 0.5 * (vetor[vet_len / 2 - 1] + vetor[vet_len / 2]);
    }

    printf("A mediana e: %.3f", mediana);

}

void bubblesort (int vetor[], int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
