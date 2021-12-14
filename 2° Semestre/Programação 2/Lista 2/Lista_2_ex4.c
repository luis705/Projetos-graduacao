#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserir();
void remover();
int procurar(int procurado);
void mostrar();
void consultar();
void alterar();
void listar();

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
		printf("\n\n/-----------------------------------------\\\n");
		printf("|                                         |\n");
		printf("|             Programa Lista              |\n");
		printf("|1 - Inserir empregado na lista           |\n");
		printf("|2 - Remover empregado da lista           |\n");
		printf("|3 - Consultar empregado por prontuario   |\n");
		printf("|4 - Alterar dados do empregado da lista  |\n");
		printf("|5 - Listagem dos empregados              |\n");
		printf("|0 - Sair do programa                     |\n");
		printf("|                                         |\n");
		printf("\\-----------------------------------------/\n");
		printf("\nInforme a opcao: ");
		fgets(aux, 10, stdin);
		op = strtol(aux, &ptr, 10);
		if (*ptr != '\n') {
			op = 5;
		}

		switch (op) {
		case 1:
			inserir();
			break;
		case 2:
			remover();
			break;
		case 3:
			consultar();
			break;
		case 4:
			alterar();
			break;
		case 5:
			listar();
			break;
		case 0:
			break;
		default:
			printf("Opcao invalida\n");
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
		printf("A lista ja esta cheia, remova algum funcionario antes de adicionar\n");
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
	int prontuario, indice, i;
	char aux[10], *ptr;

	printf("Insira o prontuario do funcionario a ser removido: \n");
	fgets(aux, 10, stdin);
	prontuario = strtol(aux, &ptr, 10);

	indice  = procurar(prontuario);

	if (indice == -1) {
		printf("O funcionario não esta na lista!");
		return;
	}

	for (i = indice + 1; i < qa; i++) {
		departamento[i-1] = departamento[i];
	}
	qa --;
	printf("O funcionario foi removido com sucesso!");
}


int procurar(int procurado) {
	int i;
	for (i = 0; i < qa; i++) {
		if (departamento[i].pront == procurado) {
			return i;
		}
	}
	return -1;
}


void consultar() {
	char aux[10], *ptr;
	int prontuario, indice;
	printf("Insira o prontuario do funcionario a ser consultado: ");
	fgets(aux, 10, stdin);
	prontuario = strtol(aux, &ptr, 10);

	indice  = procurar(prontuario);

	if (indice == -1) {
		printf("O funcionario não esta na lista!");
		return;
	}

	printf("Mostrando as informacoes do funcionario\n\n");
	printf("\tNome: %s\n\n", departamento[indice].nome);
	printf("\tProntuario: %d\n\n", departamento[indice].pront);
	printf("\tBeneficio: %.2f", departamento[indice].beneficio);
}


void alterar() {
	char aux[10], *ptr;
	empregado alterando;
	int indice, prontuario;
	float beneficio;
	printf("Insira o prontuario do funcionario a ser modificado: ");
	fgets(aux, 10, stdin);
	prontuario = strtol(aux, &ptr, 10);

	indice  = procurar(prontuario);

	if (indice == -1) {
		printf("O funcionario não esa na lista!");
		return;
	}

	printf("\nAgora preciso das novas informacoes do funcionario\n");
	printf("\n\tInisira o nome do funcionario: ");
	fgets(alterando.nome, 30, stdin);
	printf("\n\tInsira o prontuario do funcionario: ");
	fgets(aux, 10, stdin);
	prontuario = strtol(aux, &ptr, 10);
	printf("\n\tInsira o beneficio do funcionario: ");
	fgets(aux, 10, stdin);
	beneficio = strtod(aux, &ptr);

	strtok(alterando.nome, "\n");
	alterando.pront = prontuario;
	alterando.beneficio = beneficio;

	departamento[indice] = alterando;

	printf("O funcionario foi alterado com sucesso!");
}


void listar() {
	int i;
	printf("Vou listar as informacoes de todos os funcionarios para voce\n\n");

	for (i = 0; i < qa; i++) {
		printf("Funcionario %d:\n\n", i + 1);
		printf("\tNome: %s\n\n", departamento[i].nome);
		printf("\tProntuario: %d\n\n", departamento[i].pront);
		printf("\tBeneficio: %.2f\n", departamento[i].beneficio);
	}
}