#include <stdio.h>
#include <string.h>
#include "Arvore_B/arvore_B.h"
#include "Entrada_Saida/ES.h"

struct dado{
    int matricula;
    int idade;
    int cpf;
    char nome[6];
};

int main(void) {
    FILE *arq = fopen("C:\\Users\\Usuario\\Documents\\01 - Universidade\\3 - Periodo\\CTCO02 - Algoritimo e Estruturas de Dados II\\13_Trabalho2\\dataset.txt", "r");
    struct dado d;
    arvore *arv;
    int resp;

    if(!arq){
        return 1;
    }
    printf("\nQual será a ordem da árvore?\nResposta: ");
    scanf("%d", &resp);

    arv = criaArvore(resp);
    if(!arv){
        return 1;
    }

    do{
        printf("\nMenu\n1. Criar índice\n2. Procurar elementos\n3. Remover registro\n4. Sair\n\nEscolha uma opção: ");
        scanf("%d", &resp);
        switch (resp){
            case 1:
                //criarIndice();
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
