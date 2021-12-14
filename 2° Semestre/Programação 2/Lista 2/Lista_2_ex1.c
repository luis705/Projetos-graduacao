#include <stdio.h>

void bubblesort (int vetor[], int n);

int main(void) {
	int vetor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;
	bubblesort(vetor, 10);
	
	printf("Aqui esta o vetor ordenado: ");
	for (i = 0; i < 10; i++) {
		printf(" %d", vetor[i]);
	}
}

void bubblesort (int vetor[], int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if (vetor[j] < vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
