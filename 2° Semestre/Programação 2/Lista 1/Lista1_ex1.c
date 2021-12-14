#include <stdio.h>
#include <stdlib.h>

//Lista 1 Ex1: Crie as funções: cria_arquivo(char nome_arq[]),
//escreve_arquivo(char nome_arq[]) e le_arquivo(char nome_arq[])
//de modo a completar este programa. Utilize o caractere % para
//indicar o fim de dados para a função escreve arquivo

void cria_arquivo(char nome_arq[]);

void escreve_arquivo(char nome_arq[]);

void le_arquivo(char nome_arq[]);

int main(int argc, char *argv[]) {
  char nomearq[30];
  int op;
  fflush(stdin);
  printf("Entre com o nome do arquivo: \n");
  gets(nomearq);
  do {
    printf("\n Escolha a opcao: \n");
    printf("[1] - Cria arquivo \n");
    printf("[2] - Escreve no arquivo \n");
    printf("[3] - Le arquivo \n");
    printf("[4] - Sair do programa \n");
    fflush(stdin);
    scanf("%d",&op);
    switch(op) {
      case 1:
        cria_arquivo(nomearq);
        break;
      case 2:
        escreve_arquivo(nomearq);
        break;
      case 3:
        le_arquivo(nomearq);
        break;
      case 4:
        printf("Fim do programa !!! \n");
        break;
      default:
        printf("Tecla invalida !!! \n");
    }
  } while(op != 4);
  return 0;
}

void cria_arquivo(char nome_arq[]) {
  FILE *arq = fopen(nome_arq, "w");

  // Tratamento de erros
  if (arq == NULL) {
    printf("Erro ao criar o arquivo");
  }

  fclose(arq);
  return;
}

void escreve_arquivo(char nome_arq[]) {
  FILE *arq = fopen(nome_arq, "a");
  // Tratamento de erros
  if (arq == NULL) {
    printf("Nao foi possivel abrir o arquivo para escrita");
  }

  char escrever = '\0';

  printf("Digite o que voce quer escrever no arquivo finalizando com %% : ");

  while (1) {
    escrever = getchar();
    if (escrever != '%') {
      fprintf(arq, "%c", escrever);
    } else {
      break;
    }

  }

  fclose(arq);

  return;
}

void le_arquivo(char nome_arq[]) {
  FILE *arq = fopen(nome_arq, "r");

  // Tratamento de erros
  if (arq == NULL) {
    printf("Nao foi possivel abrir o arquivo para leitura");
  }

  char ler = '\0';

  while (1) {
    ler = fgetc(arq);
    if (ler  != EOF){
    printf("%c", ler);
    } else {
      break;
    }
  }
  printf("\n");

  fclose(arq);
  return;
}

