#include <stdio.h>
#include <string.h>
#define MAX 30

int main(void) {
  FILE *arqptr = fopen("funcionarios.txt", "w");
  int i;

  // Tratamento de erros ao criar o arquivo
  if (arqptr == NULL) {
    printf("O arquivo não pode ser criado");
    return 1;
  }

  char nome[100];

  // Recebe o nome compketo de cada funcionario e escreve no arquivo
  for (i = 0; i < MAX; i++) {
    printf("Funcionário %d, me diga: \n", i + 1);
    printf("\t Qual o seu nome completo: ");
    fgets(nome, 100 * sizeof(char), stdin);
    fprintf(arqptr, "%s", nome);
  }
  fclose(arqptr);
}
