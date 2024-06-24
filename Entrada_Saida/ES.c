#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criaNome(char *nome) {
    char listaLetras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    srand(time(NULL));

    for(int i = 0; i < 5; i++) {
        int index = rand() % 26;
        nome[i] = listaLetras[index]; 
    }
}

int criaMatricula() {
    int matricula=0;
    srand(time(NULL));

    for(int i = 0; i < 4; i++) {
        matricula = matricula * 10 + (rand() % 10);
    }

    return matricula;
}

char *criaDataNascimento() {
    char *data=(char*)malloc(11 * sizeof(char));
    int dia, mes, ano;
    srand(time(NULL));

    dia = rand() % 30;
    mes = 1 + rand() % 12;
    ano = 2000 + rand() % 5;

    sprintf(data, "%02d/%02d/%d", dia, mes, ano);
    return data;
}

unsigned long long criaCPF() {
    unsigned long long cpf = 0;
    srand(time(NULL));

    for(int i=0;i<11;i++) {
        cpf = cpf * 10 + (rand() % 10);
    }

    return cpf;
}