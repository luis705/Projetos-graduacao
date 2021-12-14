#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char rua[30];
  char bairro[30];
} endereco;


typedef struct {
  char nome[100];
  endereco end_residencial;
  endereco end_trabalho;
  float sal_bruto;
  float sal_liquido;
  float descontos;
} funcionario;


int main(void) {
  funcionario funcs[3];
  char *endptr;
  char aux[5];
  int i;

  for (i = 0 ; i < 3; i++) {
    // Recebe as informacoes de cada trabalhador
    printf("Funcionário %d, precisamos de seus dados:\n", i + 1);
    printf("\tNome: ");
    fgets(funcs[i].nome, 100 * sizeof(char), stdin);
    printf("\tBairro em que voce mora: ");
    fgets(funcs[i].end_residencial.bairro, 50 * sizeof(char), stdin);
    printf("\tRua em que voce mora: ");
    fgets(funcs[i].end_residencial.rua, 50 * sizeof(char), stdin);
    printf("\tBairro em que voce trabalha: ");
    fgets(funcs[i].end_trabalho.bairro, 50 * sizeof(char), stdin);
    printf("\tRua em que voce trabalha: ");
    fgets(funcs[i].end_trabalho.rua, 50 * sizeof(char), stdin);
    printf("\tSalario bruto: ");
    fgets(aux, 4 * sizeof(char), stdin);
    funcs[i].sal_bruto = strtod(aux, &endptr);
    printf("\tDescontos: ");
    fgets(aux, 4 * sizeof(char), stdin);
    funcs[i].descontos = strtod(aux, &endptr);
    funcs[i].sal_liquido = funcs[i].sal_bruto - funcs[i].descontos;
  }

  printf("\n\nSerao listadas as informacoes de todos os funcionarios\n\n");

  for (i = 0; i < 3; i ++) {
    // Antes de imrprimir na tela as informacoes, remove o \n
    // Do final de cada dado pois fgets sempre recebe \n no final
    strtok(funcs[i].nome, "\n");
    strtok(funcs[i].end_residencial.bairro, "\n");
    strtok(funcs[i].end_residencial.rua, "\n");
    strtok(funcs[i].end_trabalho.bairro, "\n");
    strtok(funcs[i].end_trabalho.rua, "\n");

    // Comeca a imprimir na tela os dados do trabalhador
    printf("\nFuncionario %d:\n", i + 1);
    printf("\tNome: %s\n", funcs[i].nome);
    printf("\tEndereco residencial: Bairro: %s Rua: %s\n", funcs[i].end_residencial.bairro, funcs[i].end_residencial.rua);
    printf("\tEndereco de trabalho: Bairro: %s Rua: %s\n",  funcs[i].end_trabalho.bairro, funcs[i].end_trabalho.rua);
    printf("\tSalario Bruto: %.2f\n", funcs[i].sal_bruto);
    printf("\tDescontos: %.2f\n", funcs[i].descontos);
    printf("\tSalario Liquido: %.2f\n", funcs[i].sal_liquido);
  }
  return 0;
}
