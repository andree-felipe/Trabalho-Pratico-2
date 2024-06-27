#include <stdio.h>
#include <string.h>
#include "Arvore_B/arvore_B.h"
#include "Entrada_Saida/ES.h"

struct registro {
    int mat;
    unsigned long long cpf;
    char *nome, *dataNasc;
};

int main(void) {
    FILE *arq;
    arvore *arv;
    registro reg;
    int resp;
    char nomeArquivo[12] = "entrada.txt";
    unsigned long long nroRegistros;

    printf("Já possui os arquivos de entrada?\n1 - Sim\n2 - Não\n0 - Sair\nOpção: ");
    scanf(" %d", &resp);
    if(resp == 2) {
        printf("Quantidade de registros: ");
        scanf(" %llu", &nroRegistros);
        if(!criaEntrada(nomeArquivo, nroRegistros)) {
            printf("Erro na criação do arquivo!");
            return 1;
        }
    }
    else if(resp == 0)
        return 0;
    

    printf("\nQual será a ordem da árvore?\nResposta: ");
    scanf("%d", &resp);

    arv = criaArvore(resp);
    if(!arv){
        printf("Erro na criação do arquivo de índice!");
        return 1;
    }

    do{
        printf("\nMenu\n1. Criar índice\n2. Procurar elementos\n3. Remover registro\n4. Sair\n\nEscolha uma opção: ");
        scanf("%d", &resp);
        switch (resp){
            case 1:
                if(!processaEntrada(nomeArquivo)) {
                    printf("Erro na abertura do arquivo!");
                    return 1;
                }
                break;
            case 2:
                //pesquisa();
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