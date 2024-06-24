#include "arvore_B.h"
#include <stdlib.h>

/*** -- Estruturas -- ***/

struct chave{
    int chave;
    int indice;
};

struct pagina{
    chave **chaves;
    int nChaves;
    int folha;
    pagina **filhos;
    pagina *pai;
};

struct arvore{
    pagina *raiz;
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
    arv->raiz = NULL;
    return arv;
}

/*
Descrição: Retorna a raiz da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Ponteiro para a raiz da árvore.
*/
pagina *getRaiz(arvore *arv){
    return arv->raiz;
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
        page->chaves = (chave**)malloc(sizeof(chave*) * (arv->ordem - 1));
    }else{
        page->chaves = (chave**)malloc(sizeof(chave*) * (arv->ordem));
    }
    if(!page->chaves){
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
int insereNo(arvore *arv, int valor, int indice){
    pagina *pageAtual, *pageAux;
    if(!arv->numElementos){
        arv->raiz = criaPagina(arv);
        if(!arv->raiz){
            return 0;
        }
        arv->raiz->chaves[0] = (chave*)malloc(sizeof(chave));
        if(!arv->raiz->chaves[0]){
            free(arv->raiz);
            return 0;
        }
        arv->raiz->chaves[0]->chave = valor;
        arv->raiz->chaves[0]->indice = indice;
        arv->raiz->nChaves = 1;
    }else{
        pageAtual = arv->raiz;
        while(!pageAtual->folha){
            pageAux = pageAtual;
            for(int i = 0; i < pageAux->nChaves; i++){
                if(valor < pageAux->chaves[i]->chave){
                    pageAtual = pageAux->filhos[i];
                }else if(i == pageAux->nChaves - 1){
                    pageAtual = pageAux->filhos[i+1];
                }
            }
        }
        if(pageAtual->nChaves < arv->ordem - 1){
            //Insere no nó
        }else{
            //Nó cheio
            if(pageAtual->pai || pageAtual->pai->nChaves == arv->ordem - 1){
                //Pai cheio
            }else{
                //Tem espaço no pai
            }
        }
    }
    return 1;
}
