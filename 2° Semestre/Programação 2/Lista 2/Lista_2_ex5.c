#include <stdio.h>

int meio(int a, int b);

int main(void) {
	int vetor[] = {15, 33, 55, 67, 73, 80, 88, 93, 98};
	int i = 0;
	int f = 9;
	int m = meio(i, f);
	int x = 33;
	int iteracao = 1;
	
	do {
		printf("/-----------------\\\n");
		printf("|                 |\n");
		printf("|   Iteracao: %d   |\n", iteracao);
		printf("|                 |\n");
		printf("|       i:%d       |\n", i);
		printf("|       f:%d       |\n", f);
		printf("|       m:%d       |\n", m);
		printf("|                 |\n");
		printf("\\-----------------/\n\n\n");

		if (x == vetor[m]){
			break;
		} else if (x > vetor[m]) {
			printf("%d\n", m);
			i = m;
		} else {
			f = m;
		}
		m = meio(i, f);
		iteracao++;
	} while (i != f);

	if (vetor[m] == x){
		printf("O valor foi encontrado!\n");
		printf("O indice e: %d\n", m);
	} else {
		printf("Infelizmente %d nao esta presente no vetor\n", x);
	}
	

}

int meio(int a, int b) {
	return (int) (a+b)/2;
}