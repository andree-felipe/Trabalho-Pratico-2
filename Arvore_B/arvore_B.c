#include "arvore_B.h"
#include <stdlib.h>

/*** -- Estruturas -- ***/

struct pagina{
    int *chaves;
    int *indice;
    int nChaves;
    int folha;
    pagina **filhos;
    pagina *pai;
};

struct arvore{
    pagina *sentinela;
    int numElementos;
    int ordem;
};

/*** -- Funções -- ***/

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

int insereNo(arvore *arv, int chave, int indice){
    if(!arv->numElementos){
        arv->sentinela->filhos = criaPagina(arv);
        if(!arv->sentinela->filhos){
            return 0;
        }
        arv->sentinela->filhos[0]->chaves[0] = chave;
        arv->sentinela->filhos[0]->indice[0] = indice;
        arv->sentinela->filhos[0]->nChaves = 1;
        arv->sentinela->filhos[0]->pai = arv->sentinela;
    }else{
        //Sinistro
    }
    return 1;
}

int removeChave(arvore *arv, int chave){
    // Declaração de Variáveis
    int indice;

    // Verificação da quantidade de elementos da Árvore.
    if(arv->numElementos < 1){
        printf("Erro ao remover o elemento '%d'.\nA árvore está vazia.\n", chave);
        return -1;
    } else {
        indice = buscaChave()
        if{

        }
    }

}

pagina* buscaPagina(pagina* pagina, int chave){
    int i=0;

    if(!pagina){
        printf("A página, de endereço '%p', não existe.", pagina);
        return -1;
    } else {
        while(i < pagina->nChaves && chave > pagina->chaves[i]){
            i++;
        }
        if(i < pagina->nChaves && chave == pagina->chaves[i]){
            return pagina;
        } else if(pagina->folha){
            return -1;
        } else {
            return buscaPagina(pagina->filhos[i], chave);
        }
    }
}