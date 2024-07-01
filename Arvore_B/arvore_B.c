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

void merge(pagina *page, arvore *arv, int pos){
    int i = 0, idx = pos;
    if(idx == arv->ordem)
        idx--;
    pagina *filho = page->filhos[idx];
    pagina *irmao = page->filhos[idx+1];
    
    irmao->chaves[irmao->nChaves] = page->chaves[pos];
    irmao->nChaves++;
    free(page->chaves[pos]);
    page->pai->nChaves--;

    while(filho->nChaves){
        // Move as chaves do irmão para o outro (filho).
        filho->chaves[filho->nChaves+i] = irmao->chaves[i];
        // irmao->chaves[i] = NULL;
        irmao->nChaves--;
        i++;
    }
    free(irmao->chaves);

    if(page->nChaves < arv->ordem/2)
        merge(page->pai, arv, pos);
}

pagina *buscaChave(struct pagina *page, int chave) {
    int i = buscaPos(page, chave);
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


int buscaPos(pagina *pagina, int chave) {
    int pos = 0;
    while (pos < pagina->nChaves && chave > pagina->chaves[pos]->chave) {
        pos++;
    }
    return pos;
}

void removeDeFolha(pagina *page, int pos){
    for(pos ; pos < page->nChaves ; pos++){
        page->chaves[pos] = page->chaves[pos+1];
    }
    free(page->chaves[pos]);
    page->nChaves--;
    return;
}

void removeDeNaoFolha(pagina *page, int pos){
    int chaves = page->chaves[pos]->chave;
    page->chaves[pos] = encontraAntecessor(page);
    removeDeFolha(buscaChave(page, page->chaves[pos]->chave), buscaPos(page, chaves));
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


int removeChave(arvore *arv, int chave){
    // Declaração de Variáveis
    int indice;
    pagina *pagina;

    // Verificação da quantidade de elementos da Árvore.
    if(arv->numElementos < 1){
        printf("Erro ao remover o elemento '%d'.\nA árvore está vazia.\n", chave);
        return 0;
    } else {
        pagina = buscaChave(arv->raiz, chave);

        if(!pagina){
            printf("Erro ao remover o elemento '%d'.\nA chave não está presente na árvore.\n");
            return 0;
        }

        indice = buscaIdx(pagina, chave);

        if(pagina->folha){
            removeDeFolha(pagina, indice);
        } else {
            struct chave *antecessor = encontraAntecessor(pagina->filhos[indice]);
            pagina->chaves[indice] = antecessor;
            removeChave(arv, antecessor->chave);
        }
    arv->numElementos--;
    return 1;
    }

}