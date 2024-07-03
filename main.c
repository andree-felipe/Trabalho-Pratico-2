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

int buscaArquivoIndice(char *nomeArquivo, int indice, registro *dadosColetados) {
    signed long tamanhoLinha = sizeof(char[34]);
    long int posicaoByte;

    FILE *arq = fopen(nomeArquivo, "r");

    // Não foi possível abrir o arquivo
    if(!arq) {
        return 0;
    }
    else {
        fseek(arq, tamanhoLinha * indice, SEEK_SET);
        fscanf(arq, "%d %s %s %ld", &dadosColetados->matricula, dadosColetados->nome, dadosColetados->dataNasc, &dadosColetados->cpf);
        printf("Nome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados->nome, dadosColetados->matricula, dadosColetados->dataNasc, dadosColetados->cpf);
    }

    fclose(arq);
}

int buscaArquivoDireto(char *nomeArquivo, int matriculaParametro, registro *dadosColetados) {
    FILE *arq = fopen(nomeArquivo, "r");
    
    if(!arq) {
        return 0;
    }
    else {
        while(fscanf(arq, "%d %s %s %ld", &dadosColetados->matricula, dadosColetados->nome, dadosColetados->dataNasc, &dadosColetados->cpf) != EOF) {
            if(dadosColetados->matricula == matriculaParametro) {
                printf("Nome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados->nome, dadosColetados->matricula, dadosColetados->dataNasc, dadosColetados->cpf);
            }
        }
    }

    fclose(arq);
}

int main(void) {
    FILE *arq;
    arvore *arv;
    pagina *page;
    registro reg;
    int resp, indice;
    char nomeArquivo[20] = "entrada.txt";

    buscaArquivoDireto(nomeArquivo, 6, &reg);

    //printf("\nQual será a ordem da árvore?\nResposta: ");
    //scanf("%d", &resp);

    arv = criaArvore(4);
    if(!arv){
        printf("Erro na criação do arquivo de índice!");
        return 1;
    }

    do{
        printf("\nMenu\n1. Criar índice\n2. Procurar elementos\n3. Remover registro\n4. Sair\n\nEscolha uma opção: ");
        scanf("%d", &resp);
        switch (resp){
            case 1:
                if(!processaEntrada(arv, nomeArquivo)) {
                    printf("Erro na abertura do arquivo!");
                    return 1;
                }
                break;
            case 2:
                srand(time(NULL));
                for(int i=0;i<30;i++){
                    buscaArquivoIndice(nomeArquivo, rand() % 10000, &reg);
                }
                printf("\n");
                for(int i=0;i<30;i++){
                    buscaArquivoDireto(nomeArquivo, rand() % 10000, &reg);
                }
                break;
            case 3:
                //removerRegistro();
                break;
            default:
                break;
        }
    }while(resp != 4);

    return 0;
}
