#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ES.h"
#include "../Arvore_B/arvore_B.h"

struct registro {
    int mat;
    unsigned long long cpf;
    char *nome, *dataNasc;
};

char *criaNome(unsigned long long seed) {
    char *nome, listaLetras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    nome = (char*)malloc(6 * sizeof(char));
    if(!nome)
        return "#-1";

    srand(seed);

    for(int i = 0; i < 5; i++) {
        int index = rand() % 26;
        nome[i] = listaLetras[index]; 
    }

    return nome;
}

int criaMatricula(unsigned long long seed) {
    int matricula = 0;

    matricula += seed-1;

    return matricula;
}

char *criaDataNascimento(unsigned long long seed) {
    char *data;
    int dia, mes, ano;

    data = (char*)malloc(11 * sizeof(char));
    if(!data)
        return "#-1";

    srand(seed);

    dia = 1 + rand() % 30;
    mes = 1 + rand() % 12;
    ano = 2000 + rand() % 5;

    sprintf(data, "%02d/%02d/%d", dia, mes, ano);
    return data;
}

unsigned long long criaCPF(unsigned long long seed) {
    unsigned long long cpf = 0;
    srand(seed);

    for(int i=0;i<11;i++) {
        cpf = cpf * 10 + (rand() % 10);
    }

    return cpf;
}

registro criaRegistro(unsigned long long seed) {
    registro reg;

    reg.mat = criaMatricula(seed);
    reg.nome = criaNome(seed);
    reg.dataNasc = criaDataNascimento(seed);        
    reg.cpf = criaCPF(seed);

    return reg;
}

int criaEntrada(char *nomeArquivo, unsigned long long nroRegistos) {
    registro reg;
    FILE *file;
    file = fopen(nomeArquivo, "w");
    if(!file)
        return 0;

    for(unsigned long long i=0;i<nroRegistos-1;i++) {
        reg = criaRegistro(i+1);
        fprintf(file, "%04d %s %s %011llu\n", reg.mat, reg.nome, reg.dataNasc, reg.cpf);
    }
    reg = criaRegistro(nroRegistos);
    fprintf(file, "%04d %s %s %llu", reg.mat, reg.nome, reg.dataNasc, reg.cpf);

    fclose(file);
    return 1;
}

int processaEntrada(char *nomeArquivo) {
    registro reg;
    FILE *file;
    file = fopen(nomeArquivo, "r");
    if(!file)
        return 0;

    while(!feof(file)) {
        fscanf(file, "%04d %s %s %llu", &reg.mat, reg.nome, reg.dataNasc, &reg.cpf);
        /*
        if(!insereNo()) {
            printf("ERRO!!");
            return -1;
        }
        */
    }

    fclose(file);
    return 1;
}

void printRegistro(registro reg) {
    printf("%04d %s %s %llu\n", reg.mat, reg.nome, reg.dataNasc, reg.cpf);
}