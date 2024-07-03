#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Arvore_B/arvore_B.h"

/*** - Estruturas -- ***/

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

/*** -- Funções -- ***/

/*
Descrição: Função responsável por pegar o índice e com o tamanho da linha achar a linha com o valor passado.
Entrada: Inteiro do índice, ponteiro para o arquivo.
Saída: Nada.
*/
void buscaArquivoIndice(int indice, FILE *arq){
    registro dadosColetados;
    signed long tamanhoLinha = sizeof(char[35]);
    fseek(arq, tamanhoLinha * indice, SEEK_SET); //Colocando o ponteiro do arquivo na linha do registro.
    fscanf(arq, "%d %s %s %ld", &dadosColetados.matricula, dadosColetados.nome, dadosColetados.dataNasc, &dadosColetados.cpf);
    printf("\nNome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados.nome, dadosColetados.matricula, dadosColetados.dataNasc, dadosColetados.cpf);
}

/*
Descrição: Função responsável por fazer a busca direta no arquivo, ela lê o arquivo até achar o registro correspondente.
Entrada: Inteiro da matrícula, ponteiro para o arquivo.
Saída: Nada.
*/
void buscaArquivoDireto(int mat, FILE *arq){
    registro dadosColetados;
    rewind(arq); //Colocando o ponteiro do arquivo no início.
    dadosColetados.matricula = -1;
    while(!feof(arq) && dadosColetados.matricula != mat) {
        fscanf(arq, "%d %s %s %ld", &dadosColetados.matricula, dadosColetados.nome, dadosColetados.dataNasc, &dadosColetados.cpf);
        if(dadosColetados.matricula == mat) {
            printf("\nNome: %s | Matricula: %04d | Data de Nascimento: %s | CPF: %011ld\n", dadosColetados.nome, dadosColetados.matricula, dadosColetados.dataNasc, dadosColetados.cpf);
        }
    }
}

/*
Descrição: Função principal, responsável por pedir as entradas do usuário, e chamar as funções de busca e da árvore.
Entrada: Nada.
Saída: 0 - Sucesso, 1 - Erro.
*/
int main(void) {
    FILE *arq;
    arvore *arv;
    metricas btree, direto;
    clock_t inicio, fim;
    int resp, indice, mat, qtdPesquisa=10000, ver;
    double tempo;
    char nomeArquivoResultados[20], nomeArquivo[20] = "entrada.txt";

    //Pedindo para o usuário digitar a ordem da árvore.
    printf("\nQual será a ordem da árvore? (Somente ordens pares).\nResposta: ");
    scanf("%d", &resp);
    if(resp % 2 != 0){
        printf("\nOrdem não par!");
        return 1;
    }

    //Criando a árvore b com a ordem digitada.
    arv = criaArvore(resp);
    if(!arv){
        printf("\nErro na criação da árvore!");
        return 1;
    }

    //Lendo o arquivo informado.
    arq = fopen(nomeArquivo, "r");
    if(!arq){
        printf("\nErro na abertura do arquivo.");
        return 1;
    }

    //Iniciando o menu.
    do{
        printf("\nMenu\n1. Criar índice\n2. Procurar elementos\n3. Remover registro\n4. Sair\n\nEscolha uma opção: ");
        scanf("%d", &resp);
        switch (resp){
            case 1:
                //Todos as entradas no arquivo serão jogadas para a árvore.
                if(!processaEntrada(arv, arq)) {
                    printf("\nErro na inserção da árvore.");
                    return 1;
                }
                break;
            case 2:
                printf("\n1. Busca específica\n2. Busca valores aleatórios\n\nEscolha uma opção: ");
                scanf("%d", &resp);
                if(resp == 1){
                    printf("\nInforme a matrícula que você deseja buscar: ");
                    scanf("%d", &mat);
                    //Início da busca na B-Tree.
                    inicio = clock();
                    indice = buscaChave(getRaiz(arv), mat);
                    buscaArquivoIndice(indice, arq);
                    fim = clock();
                    //Fim da busca na B-Tree.
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    printf("Tempo para a busca por índice: %f\n", tempo);
                    //Início da busca direta.
                    inicio = clock();
                    buscaArquivoDireto(mat, arq);
                    fim = clock();
                    //Fim da busca direta.
                    tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                    printf("Tempo para a busca direta: %f\n", tempo);
                }else{
                    //Setando as métricas como 0.
                    btree.tMin = btree.tMax = btree.media = 0;
                    direto.tMin = direto.tMax = direto.media = 0;
                    //Gerando uma nova seed.
                    srand(time(NULL));
                    //Fazendo as n pesquisas aleatórias.
                    for(int i = 0; i < qtdPesquisa; i++){
                        mat = rand() % 11000;
                        //Início da busca na B-Tree.
                        inicio = clock();
                        indice = buscaChave(getRaiz(arv), mat);
                        buscaArquivoIndice(indice, arq);
                        fim = clock();
                        //Fim da busca na B-Tree.
                        //Calculando o tempo, e salvando nas variáveis.
                        tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                        btree.media += tempo;
                        if(btree.tMin == 0 && btree.tMax == 0)
                            btree.tMin = btree.tMax = tempo;
                        else if(tempo < btree.tMin)
                            btree.tMin = tempo;
                        else if(tempo > btree.tMax)
                            btree.tMax = tempo;
                        //Início da busca direta.
                        inicio = clock();
                        buscaArquivoDireto(mat, arq);
                        fim = clock();
                        //Fim da busca direta.
                        //Calculando o tempo, e salvando nas variáveis.
                        tempo = (double)(fim-inicio)/(CLOCKS_PER_SEC/1000);
                        direto.media += tempo;
                        if(direto.tMin == 0 && direto.tMax == 0)
                            direto.tMin = direto.tMax = tempo;
                        else if(tempo < direto.tMin)
                            direto.tMin = tempo;
                        else if(tempo > direto.tMax)
                            direto.tMax = tempo;
                    }
                    //Calculando a média de ambos os casos.
                    btree.media /= (float)qtdPesquisa;
                    direto.media /= (float)qtdPesquisa;
                    //Salvando em um arquivo.
                    printf("Nome do arquivo: ");
                    scanf(" %[^\n]", nomeArquivoResultados);
                    geraArquivoResultados(nomeArquivoResultados, btree, direto);
                }
                break;
            case 3:
                printf("\nDigite o elemento que você deseja remover: ");
                scanf("%d", &mat);
                printf("\nNúmero de elementos na árvore: %d\n", getNumElementos(arv));
                imprimeArvore(getRaiz(arv), 0);
                printf("\n");
                ver = deleta(arv, mat);
                if(ver == 0){
                    printf("\nElemento não encontrado.\n");
                }else if(ver == -1){
                    printf("\nÁrvore vazia.\n");
                }else{
                    printf("\nNúmero de elementos na árvore: %d\n", getNumElementos(arv));
                    imprimeArvore(getRaiz((arv)), 0);
                    printf("\n");
                }
                break;
                break;
            default:
                break;
        }
    }while(resp != 4);
    free(arv);
    fclose(arq);
    return 0;
}
