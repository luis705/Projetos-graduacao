#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void inserir();
void remover();
void consultar();
void listar();
//void trocar(empregado *a, empregado *b);

typedef struct {
	int pront;
	char nome[30];
	float beneficio;
} empregado;

empregado departamento[5];
const int max = 5;
int qa, op;



int main(int argc, char *argv[]) {
	char aux[10];
	char *ptr;
	qa=0;
	do {
		printf("\n\n/---------------------------------------\\\n");
		printf("|            Programa Lista             |\n");
		printf("|                                       |\n");
		printf("|1 - Inserir empregado na fila          |\n");
		printf("|2 - Remover empregado da fila          |\n");
		printf("|3 - Consultar empregado da fila        |\n");
		printf("|4 - Listagem dos empregados na fila    |\n");
		printf("|0 - Sair do programa                   |\n");
		printf("|                                       |\n");
		printf("\\---------------------------------------/\n");
		
		printf("\nInforme a opcao: ");
		fgets(aux, 10, stdin);
		op = strtol(aux, &ptr, 10);
		if (*ptr != '\n') {
			op = 5;
		}

		switch (op) {case 1:
			inserir();
			break;
		case 2:
			remover();
			break;
		case 3:
			consultar();
			break;
		case 4:
			listar();
			break;
		case 0:
			break;
		default:
			printf("opcao invalida\n");
			break;
		}
	}
	while(op != 0);
	return 0;
}


void inserir() {
	char aux[10], *ptr;
	int prontuario;
	float beneficio;
	empregado adicionando;

	if (qa == max) {
		printf("\nA lista ja esta cheia, remova algum funcionario antes de adicionar\n");
		return;
	}
	printf("\nAgora preciso das informacoes do funcionario\n");
	printf("\n\tInisira o nome do funcionario a ser adicionado: ");
	fgets(adicionando.nome, 30, stdin);
	printf("\n\tInsira o prontuario do funcionario: ");
	fgets(aux, 10, stdin);
	prontuario = strtol(aux, &ptr, 10);
	printf("\n\tInsira o beneficio do funcionario: ");
	fgets(aux, 10, stdin);
	beneficio = strtod(aux, &ptr);

	strtok(adicionando.nome, "\n");
	adicionando.pront = prontuario;
	adicionando.beneficio = beneficio;

	departamento[qa] = adicionando;
	qa ++;

	printf("\nO funcionario foi adicionado com sucesso!\n\n");
}


void remover() {
	if (qa == 0) {
		printf("\nA lista ja esta vazia!");
		return;
	}

	int i;

	for (i = 1; i < qa; i++) {
		//trocar(departamento[i-1], )
		departamento[i-1] = departamento[i];
	}
	qa --;
	printf("\nO funcionario foi removido com sucesso!\n");

}


void consultar() {
	printf("\nAqui vao as informacoes do primeiro funcionario:\n\n");
	printf("\tNome: %s\n", departamento[0].nome);
	printf("\tProntuario: %d\n", departamento[0].pront);
	printf("\tBeneficio: %.2f\n", departamento[0].beneficio);
}


void listar() {
	int i;
	printf("Vou listar as informacoes de todos os funcionarios para voce\n");

	for (i = 0; i < qa; i++) {
		printf("\nFuncionario %d\n", i + 1);
		printf("\tNome: %s\n", departamento[i].nome);
		printf("\tProntuario: %d\n", departamento[i].pront);
		printf("\tBeneficio: %.2f\n", departamento[i].beneficio);

	}

};
