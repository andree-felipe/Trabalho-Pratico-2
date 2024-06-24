#include "arvore_B.h"
#include <stdlib.h>

/*** -- Estruturas -- ***/

struct pagina{
    int *chaves;
    int *indice;
    int nChaves;
    int folha;
    pagina *filhos;
    pagina *pai;
};

struct arvore{
    pagina *sentinela;
    int numElementos;
    int ordem;
};

/*** -- Funções -- ***/

/*
Descrição: Cria uma estrutura da árvore b.
Entrada: Inteiro da ordem da árvore.
Saída: Ponteiro para a árvore; NULL em caso de erro.
*/
arvore *criaArvore(int ordem){
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv){
        return NULL;
    }
    arv->numElementos = 0;
    arv->ordem = ordem;
    arv->sentinela = (pagina*)malloc(sizeof(pagina));
    if(!arv->sentinela){
        free(arv);
        return NULL;
    }
    arv->sentinela->chaves = (int*)malloc(sizeof(int));
    if(!arv->sentinela->chaves){
        free(arv->sentinela);
        free(arv);
        return NULL;
    }
    arv->sentinela->chaves[0] = -1000;
    arv->sentinela->indice = (int*)malloc(sizeof(int));
    if(!arv->sentinela->indice){
        free(arv->sentinela->chaves);
        free(arv->sentinela);
        free(arv);
        return NULL;
    }
    arv->sentinela->indice[0] = -1;
    arv->sentinela->folha = 0;
    arv->sentinela->nChaves = 1;
    arv->sentinela->filhos = NULL;
    arv->sentinela->pai = NULL;
    return arv;
}

/*
Descrição: Cria uma estrutura da página.
Entrada: Ponteiro para a árvore b.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaPagina(arvore *arv){
    pagina *page = (pagina*)malloc(sizeof(pagina));
    if(!page){
        return NULL;
    }
    if(arv->ordem % 2 == 0){
        page->chaves = (int*)malloc(sizeof(int) * (arv->ordem - 1));
    }else{
        page->chaves = (int*)malloc(sizeof(int) * (arv->ordem));
    }
    if(!page->chaves){
        free(page);
        return NULL;
    }
    if(arv->ordem % 2 == 0){
        page->indice = (int*)malloc(sizeof(int) * (arv->ordem - 1));
    }else{
        page->indice = (int*)malloc(sizeof(int) * (arv->ordem));
    }
    if(!page->indice){
        free(page->chaves);
        free(page);
        return NULL;
    }
    page->pai = NULL;
    page->filhos = NULL;
    page->nChaves = 0;
    page->folha = 1;
    return page;
}

/*
Descrição: Insere um elemento na árvore, e chama as funções de correção dependendo do caso.
Entrada: Ponteiro para a árvore b, inteiro da chave, inteiro da linha.
Saída: 1 - Sucesso, 0 - Erro.
*/
int insereNo(arvore *arv, int chave, int indice){
    pagina *pageAtual, *pageAux;
    if(!arv->numElementos){
        arv->sentinela->filhos = criaPagina(arv);
        if(!arv->sentinela->filhos){
            return 0;
        }
        arv->sentinela->filhos->chaves[0] = chave;
        arv->sentinela->filhos->indice[0] = indice;
        arv->sentinela->filhos->nChaves = 1;
        arv->sentinela->filhos->pai = arv->sentinela;
    }else{
        pageAtual = arv->sentinela->filhos;
        while(!pageAtual->folha){
            pageAux = pageAtual;
            for(int i = 0; i < pageAux->nChaves; i++){
                if(chave < pageAux->chaves[i]){
                    pageAtual = &pageAux->filhos[i];
                }else if(i == pageAux->nChaves - 1){
                    pageAtual = &pageAux->filhos[i+1];
                }
            }
        }
        if(pageAtual->nChaves < arv->ordem - 1){
            //Insere no nó
        }else{
            //Nó cheio
            if(pageAtual->pai == arv->sentinela || pageAtual->pai->nChaves == arv->ordem - 1){
                //Pai cheio
            }else{
                //Tem espaço no pai
            }
        }
    }
    return 1;
}
