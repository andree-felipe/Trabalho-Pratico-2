#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Arvore_B/arvore_B.h"
#include <time.h>

/*** -- Estruturas -- ***/

typedef struct registro{
    int mat;
    long int cpf;
    char nome[6];
    char data[11];
}registro;

typedef struct metricas{
    double tMin, tMax;
    float media;
}metricas;

/*** -- Funções -- ***/

/*
Descrição: Função que busca no arquivo o dado com base no índice informado. No caso a função usa o fseek(), com o tamanho da linha já estabelecido como 34 bytes.
Entrada: Inteiro do índice, ponteiro para o arquivo.
Saída: Nada.
*/
void buscaArquivoIndice(int indice, FILE *arq) {
    signed long tamanhoLinha = sizeof(char[34]);
    registro reg;
    fseek(arq, tamanhoLinha * indice, SEEK_SET);
    fscanf(arq, "%d %s %s %ld", &reg.mat, &reg.nome, &reg.data, &reg.cpf);
    printf("\nNome: %s | Matricula: %d | Data de Nascimento: %s | CPF: %ld\n", reg.nome, reg.mat, reg.data, reg.cpf);
}

/*
Descrição: Função que varre o arquivo em busca de um dado igual ao informado.
Entrada: Inteiro da matrícula (dado a ser procurado), ponteiro para o arquivo.
Saída: Nada.
*/
void buscaArquivoDireto(int mat, FILE *arq) {
    registro reg;
    rewind(arq);
    reg.mat = -1;
    while(!feof(arq) && reg.mat != mat) {
        fscanf(arq, "%d %s %s %ld", &reg.mat, reg.nome, reg.data, &reg.cpf);
        if(reg.mat == mat) {
            printf("Nome: %s | Matricula: %d | Data de Nascimento: %s | CPF: %ld\n", reg.nome, reg.mat, reg.data, reg.cpf);
        }
    }
}

int main(void) {
    FILE *arq = fopen("C:\\Users\\Usuario\\Documents\\01 - Universidade\\3 - Periodo\\CTCO02 - Algoritimo e Estruturas de Dados II\\13_Trabalho2\\entrada.txt", "r");
    metricas btree, direto;
    arvore *arv;
    int resp, indice, mat;
    clock_t inicio, fim;
    double tempo;

    arv = criaArvore(4);
    do{
        printf("\nMENU");
        printf("\n1. Criar índice");
        printf("\n2. Procurar elementos");
        printf("\n4. Sair");
        printf("\nResposta: ");
        scanf("%d", &resp);

        switch(resp){
            case 1:
                if(!processaEntrada(arv, arq)){
                    return 1;
                }
                break;
            case 2:
//                printf("\nInforme a matrícula que você deseja ler: ");
//                scanf("%d", &mat);
//                indice = buscaChave(getRaiz(arv), mat);
//                if(indice == -1){
//                    printf("\nElemento não encontrado.\n");
//                }else {
//                    buscaArquivoIndice(indice, arq);
//                }
                btree.tMin = btree.tMax = 0;
                direto.tMin = direto.tMax = 0;
                srand(time(NULL));
                for(int i = 0; i < 30; i++){
                    mat = rand() % 10000;
                    inicio = clock();
                    indice = buscaChave(getRaiz(arv), mat);
                    buscaArquivoIndice(indice, arq);
                    fim = clock();
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    if(btree.tMin == 0 && btree.tMax == 0){
                        btree.tMin = btree.tMax = tempo;
                    }else if(tempo < btree.tMin){
                        btree.tMin = tempo;
                    }else if(tempo > btree.tMax){
                        btree.tMax = tempo;
                    }

                    inicio = clock();
                    buscaArquivoDireto(mat, arq);
                    fim = clock();
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    if(direto.tMin == 0 && direto.tMax == 0){
                        direto.tMin = direto.tMax = tempo;
                    }else if(tempo < direto.tMin){
                        direto.tMin = tempo;
                    }else if(tempo > direto.tMax){
                        direto.tMax = tempo;
                    }
                }
                printf("\n\nTempo mínimo B-Tree: %f", btree.tMin);
                printf("\n\nTempo máximo B-Tree: %f", btree.tMax);
                printf("\n\nTempo mínimo direto: %f", direto.tMin);
                printf("\n\nTempo máximo direto: %f\n", direto.tMax);
                break;
            default:
                break;
        }
    }while(resp != 4);

    return 0;
}
