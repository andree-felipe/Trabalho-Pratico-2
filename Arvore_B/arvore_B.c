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
    for(int i = 0; i < arv->ordem-1; i++){
        page->chaves[i] = NULL;
    }
    if(arv->ordem % 2 == 1){
        page->chaves[arv->ordem-1] = NULL;
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
    pagina *pageAtual, *pageAux; //pageAtual percorre a árvore, pageAux auxilia salvando o pai.
    //Verificando se a árvore está vazia, se estiver apenas cria uma página e vincula com a raiz, se não estiver procure a página.
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
        //Enquanto o pageAtual não chegar na folha, continue procurando.
        while(!pageAtual->folha){
            pageAux = pageAtual; //Salvando o pai.
            //Verificando em qual filho entrar.
            for(int i = 0; i < pageAux->nChaves && pageAtual == pageAux; i++){
                if(valor < pageAux->chaves[i]->chave){
                    pageAtual = pageAux->filhos[i];
                }else if(i == pageAux->nChaves - 1){
                    pageAtual = pageAux->filhos[i+1];
                }
            }
        }
        //Verificando se a página atual está cheia, se não estiver insere a nova chave, se estiver split.
        if(pageAtual->nChaves < arv->ordem - 1){
            if(!insereFolha(pageAtual, valor, indice)){
                return 0;
            }
        }else{
            //Nó cheio
            if(pageAtual->pai && pageAtual->pai->nChaves == arv->ordem - 1){
                //Pai cheio
            }else{
                //Tem espaço no pai
            }
        }
    }
    return 1;
}

/*
Descrição: Aloca uma nova estrutura de chave, e salva ela na lista de chaves da página.
Entrada: Ponteiro para a página onde será inserido, inteiro da chave, inteiro da linha.
Saída: 1 - Sucesso, 0 - Erro.
*/
int insereFolha(pagina *page, int valor, int indice){
    int pos = page->nChaves - 1;
    page->chaves[pos + 1] = (chave*)malloc(sizeof(chave));
    if(!page->chaves[pos + 1]){
        return 0;
    }
    while(pos >= 0 && valor < page->chaves[pos]->chave){
        page->chaves[pos+1]->chave = page->chaves[pos]->chave;
        page->chaves[pos+1]->indice = page->chaves[pos]->indice;
        pos--;
    }
    page->chaves[pos + 1]->chave = valor;
    page->chaves[pos + 1]->indice = indice;
    page->nChaves+=1;
    return 1;
}

int split(arvore *arv, pagina *page) {
    pagina *newPage;
    int pos=page->nChaves-1, meio=(page->nChaves - 1) / 2;
    int esq, dir;
    //Guarda o pai da página
    pagina *pai = page->pai;
    //Guarda a chave mediana da página
    chave *chaveMed = page->chaves[meio];

    //Insere a chave do meio de forma ordenada no pai
    while(pos >= 0 && chaveMed->chave < pai->chaves[pos]->chave) {
        pai->chaves[pos+1]->chave = pai->chaves[pos]->chave;
        pai->chaves[pos+1]->indice = pai->chaves[pos]->indice;
        pos--;
    }
    pai->chaves[pos + 1]->chave = chaveMed->chave;
    pai->chaves[pos + 1]->indice = chaveMed->indice;
    pai->nChaves++;

    //Faz a subdivisão da página
    newPage = criaPagina(arv);
    //Subdivisão da esquerda
    //Copia todos os elementos à esquerda de page para newPage
    esq = meio - 1;
    while(esq >= 0) {
        newPage->chaves[esq]->chave = page->chaves[esq]->chave;
        newPage->chaves[esq]->indice = page->chaves[esq]->indice;
        newPage->nChaves++;
        esq--;
    }
    //Subdivisão da direita
    //Dá shift para a esquerda em todos os elemntos à direita de page
    dir = meio + 1;
    while(dir > 0) {
        page->chaves[dir-1]->chave = page->chaves[dir]->chave;
        page->chaves[dir-1]->indice = page->chaves[dir]->indice;
        page->nChaves--;
        dir--;
    }

    //Atualiza os ponteiros do pai
    pai->filhos[pos-1] = newPage;
    pai->filhos[pos] = page;
    return 1;
}
