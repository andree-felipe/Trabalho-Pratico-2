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

void merge(pagina *page, arvore *arv, int idx){
    int i = 0;
    // Idx indica a posição do pai direto entre as paginas do merge
    pagina *filho = page->filhos[idx];
    pagina *irmao = page->filhos[idx + 1];

    filho->chaves[filho->nChaves] = page->chaves[idx];
    while(filho->nChaves){
        // Move as chaves do irmão para o outro (filho).
        irmao->chaves[irmao->nChaves+i] = filho->chaves[i];
        filho->nChaves--;
        i++;
    }
    if(page->pai->nChaves < arv->ordem%2)
        merge(page->pai, arv, idx);
}

// Função recursiva para buscar a chave na árvore B
pagina *buscaChave(struct pagina *page, int chave) {
    int i = buscaIdx(page, chave);
    // Se a chave é encontrada nesta página, retorna a página
    if (i < page->nChaves && page->chaves[i]->chave == chave) {
        return page;
    }   
    // Se a página é uma folha, a chave não está presente
    if (page->folha) {
        return NULL;
    }    
    // Se a página não é uma folha, busca recursivamente no filho apropriado
    return buscar(page->filhos, chave);
}

// Função para encontrar a chave antecessora 
chave *encontraAntecessor(pagina *pagina) {
    while (!pagina->folha) {
        pagina = pagina->filhos[pagina->nChaves];
    }
    return pagina->chaves[pagina->nChaves - 1];
}


// Função auxiliar para buscar o idx de uma página
int buscaIdx(pagina *pagina, int chave) {
    int idx = 0;
    while (idx < pagina->nChaves && chave > pagina->chaves[idx]->chave) {
        idx++;
    }
    return idx;
}

void removeDeFolha(pagina *page, int idx){
    for(idx ; idx < page->nChaves ; idx++){
        page->chaves[idx] = page->chaves[idx+1];
    }
    page->chaves[idx] = NULL;
    page->nChaves--;
    return;
}

void removeDeNaoFolha(pagina *page, int idx){
    int k = page->chaves[idx]->chave;
    page->chaves[idx]->chave = encontraAntecessor(page);
    removeDeFolha(buscaChave(page, page->chaves[idx]->chave), buscaIdx(page, k));
    return;
}

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
pagina *criapagina(arvore *arv){
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
        arv->raiz = criapagina(arv);
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
            if(pageAtual->pai || pageAtual->pai->nChaves == arv->ordem - 1){
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
