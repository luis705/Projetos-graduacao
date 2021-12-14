#include <stdio.h>
#include <string.h>
#define NUM 10


typedef struct {
    char placa[10];
    int h_ent;
    int min_ent;
    int h_saida;
    int min_saida;
} carro;

float calcula_preco(carro usuario);
void adiciona_carro(carro carros[], int i);
void remove_carro(carro carros[], int i);
void lista_carros(carro carros[], int i);
void limpa_buffer();

int main(void) {
    carro carros[NUM];

    printf("Ha %d carros entrando!\n", NUM);
    for (int i = 0; i < NUM; i++) {
        printf("\nPrecisamos das informacoes do carro %d\n", i+1);
        adiciona_carro(carros, i);
        limpa_buffer();
    }

    printf("\n\nOs carros estacionados serao listados\n");
    lista_carros(carros, NUM);

    printf("\n\nOh, eles ja estao saindo...\n");
    for (int i = 0; i < NUM; i++) {
        printf("\n\n");
        remove_carro(carros, i);
    }

}

// Calcula o preco da estadia
float calcula_preco(carro usuario) {
    int horas = usuario.h_saida - usuario.h_ent;
    int minutos = usuario.min_saida - usuario.min_ent;
    if (horas < 0) {
        horas += 24;
    }
    if (minutos < 0 ) {
        horas--;
        minutos = 60 - minutos;
    }

    printf("Obigado pela preferencia, voce esteve estacionado por %d horas e %d minutos\n", horas, minutos);

    if (horas == 0 && minutos <= 10) {
        return 0;
    } else if (horas == 0) {
        return 9;
    } else if (horas < 2) {
        return 13;
    } else if (horas < 16) {
        return 13 + (horas - 2) * 2.5;
    } else {
        return 50;
    }
}

// Adiciona um carro ao estacionamento
void adiciona_carro(carro carros[], int i) {
    printf("\tInsira a placa do carro: ");
    fgets(carros[i].placa, 9, stdin);
    strtok(carros[i].placa, "\n");

    printf("\tInsira a hora e o minuto de entrada do carro separados por espaco como no exemplo hh mm: ");
    scanf("%d %d", &carros[i].h_ent, &carros[i].min_ent);

}

// Remove o carro e imprime na tela o preco da estadia
void remove_carro(carro carros[], int i){
    printf("O carro de placa %s esta saindo.\n",carros[i].placa);

    printf("\tInsira a hora e o minuto de saida do carro separados por espaco como no exemplo hh mm: ");
    scanf("%d %d", &carros[i].h_saida, &carros[i].min_saida);

    float preco = calcula_preco(carros[i]);

    printf("O valor total e de %.2f reais.\n", preco);

}

// Lista os carros atualmente estacionados
void lista_carros(carro carros[], int i) {
    for (int j = 0; j < i; j++) {
        printf("\tPlaca %s Entrada %.2d:%.2d\n", carros[j].placa, carros[j].h_ent, carros[j].min_ent);
    }
}

// Utilizar o fflush(stdin) apenas não estava limpando completamente o buffer
// Para isso criei esta funcao que le todos os caracteres do stdin
void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' &&  c!= EOF){}
}
