#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arvore_B/arvore_B.h"
#include "Entrada_Saida/ES.h"

typedef struct registro {
    int matricula;
    long int cpf;
    char dataNasc[11];
    char nome[6];
}registro;

typedef struct metricas {
    double tMin, tMax;
    float media;
}metricas;

void buscaArquivoIndice(int indice, FILE *arq){
    registro dadosColetados;
    signed long tamanhoLinha = sizeof(char[35]);

    fseek(arq, tamanhoLinha * indice, SEEK_SET);
    fscanf(arq, "%d %s %s %ld", &dadosColetados.matricula, dadosColetados.nome, dadosColetados.dataNasc, &dadosColetados.cpf);
    printf("Nome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados.nome, dadosColetados.matricula, dadosColetados.dataNasc, dadosColetados.cpf);
}

void buscaArquivoDireto(int mat, FILE *arq){
    registro dadosColetados;

    rewind(arq);
    dadosColetados.matricula = -1;
    while(!feof(arq) && dadosColetados.matricula != mat) {
        fscanf(arq, "%d %s %s %ld", &dadosColetados.matricula, dadosColetados.nome, dadosColetados.dataNasc, &dadosColetados.cpf);
        if(dadosColetados.matricula == mat) {
            printf("Nome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados.nome, dadosColetados.matricula, dadosColetados.dataNasc, dadosColetados.cpf);
        }
    }
}

int main(void) {
    FILE *arq;
    arvore *arv;
    pagina *page;
    registro reg;
    metricas btree, direto;
    clock_t inicio, fim;
    int resp, indice, mat, qtdPesquisa=30;
    double tempo;
    char nomeArquivoResultados[20], nomeArquivo[20] = "entrada.txt";

    //printf("\nQual será a ordem da árvore?\nResposta: ");
    //scanf("%d", &resp);

    arv = criaArvore(4);
    if(!arv){
        printf("Erro na criação do arquivo de índice!");
        return 1;
    }

    arq = fopen(nomeArquivo, "r");

    do{
        printf("\nMenu\n1. Criar índice\n2. Procurar elementos\n3. Remover registro\n4. Sair\n\nEscolha uma opção: ");
        scanf("%d", &resp);
        switch (resp){
            case 1:
                if(!processaEntrada(arv, arq)) {
                    printf("Erro na abertura do arquivo!");
                    return 1;
                }
                break;
            case 2:
                btree.tMin = btree.tMax = btree.media = 0;
                direto.tMin = direto.tMax = direto.media = 0;
                srand(time(NULL));
                for(int i = 0; i < qtdPesquisa; i++){
                    mat = rand() % 11000;
                    inicio = clock();
                    indice = buscaChave(getRaiz(arv), mat);
                    buscaArquivoIndice(indice, arq);
                    fim = clock();
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    btree.media += tempo;
                    if(btree.tMin == 0 && btree.tMax == 0)
                        btree.tMin = btree.tMax = tempo;
                    else if(tempo < btree.tMin)
                        btree.tMin = tempo;
                    else if(tempo > btree.tMax)
                        btree.tMax = tempo;
                    
                    inicio = clock();
                    buscaArquivoDireto(mat, arq);
                    fim = clock();
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    direto.media += tempo;
                    if(direto.tMin == 0 && direto.tMax == 0)
                        direto.tMin = direto.tMax = tempo;
                    else if(tempo < direto.tMin)
                        direto.tMin = tempo;
                    else if(tempo > direto.tMax)
                        direto.tMax = tempo;
                    
                }
                btree.media /= (float)qtdPesquisa;
                direto.media /= (float)qtdPesquisa;

                printf("Nome do arquivo: ");
                scanf(" %[^\n]", nomeArquivoResultados);
                geraArquivoResultados(nomeArquivoResultados, btree, direto);
                break;
            case 3:
                break;
            default:
                break;
        }
    }while(resp != 4);

    fclose(arq);
    return 0;
}
