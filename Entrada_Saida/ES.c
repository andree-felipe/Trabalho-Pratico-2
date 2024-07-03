#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ES.h"

struct registro {
    int mat;
    long int cpf;
    char *dataNasc;
    char *nome;
};

struct metricas {
    double tMin, tMax;
    float media;
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

long int criaCPF(unsigned long long seed) {
    long int cpf = 0;
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
        fprintf(file, "%05d %s %s %011ld\n", reg.mat, reg.nome, reg.dataNasc, reg.cpf);
    }
    reg = criaRegistro(nroRegistos);
    fprintf(file, "%05d %s %s %011ld", reg.mat, reg.nome, reg.dataNasc, reg.cpf);

    fclose(file);
    return 1;
}

void geraArquivoResultados(char *nomeArquivo, metricas btree, metricas direto){
    FILE *file;
    char tipo[12]="Por índice", analise[8]="Mínimo", path[29] = "Resultados/";
    strcat(path, nomeArquivo);

    file = fopen(path, "w");
    if(!file){
        printf("Impossiível criar o arquivo\n");
        return;
    }

    fprintf(file, "Tipo de busca, Análise(tempo), Tempo(ms)\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            if(i == 0){
                switch(j){
                    case 0:
                        fprintf(file, "%s, %s, %lf\n", tipo, analise, btree.tMin);
                        strcpy(analise, "Média");
                        break;
                    case 1:
                        fprintf(file, "%s, %s, %f\n", tipo, analise, btree.media);
                        strcpy(analise, "Máximo");
                        break;
                    case 2:
                        fprintf(file, "%s, %s, %lf\n", tipo, analise, btree.tMax);
                        break;
                }
            }
            else{
                switch(j){
                    case 0:
                        strcpy(analise, "Mínimo");
                        fprintf(file, "%s, %s, %lf\n", tipo, analise, direto.tMin);
                        strcpy(analise, "Média");
                        break;
                    case 1:
                        fprintf(file, "%s, %s, %f\n", tipo, analise, direto.media);
                        strcpy(analise, "Máximo");
                        break;
                    case 2:
                        fprintf(file, "%s, %s, %lf", tipo, analise, direto.tMax);
                        break;
                }
            }
        }
        strcpy(tipo, "Direto");
    }
    fclose(file);
}