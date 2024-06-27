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
            //Nó cheio -> Duas abordagens: Ordem par divide e depois insere, ordem ímpar insere e depois divide.
            if(arv->ordem % 2 == 0){
                //Ordem par
            }else{
                //Ordem ímpar
                if(!insereFolha(pageAtual, valor, indice)){
                    return 0;
                }
            }
//            if(pageAtual->pai && pageAtual->pai->nChaves == arv->ordem - 1){
//                //Pai cheio
//            }else{
//                //Tem espaço no pai
//            }
        }
    }
    arv->numElementos+=1;
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

/*
Descrição: Função que insere um elemento em um pai, sendo que a árvore é de ordem ímpar.
Entrada: Ponteiro para a árvore, ponteiro para a página onde o elemento original foi inserido, valor do elemento que será inserido no pai, e indice.
Saída: 1 - Sucesso, 0 - Erro.
*/
int inserePImpar(arvore *arv, pagina *page, int valor, int indice){
    if(!page->pai){
        //O nó é uma raiz.
        //Criando uma página para o pai.
        page->pai = criaPagina(arv);
        if(!page->pai){
            return 0;
        }
        //Setando sua condição como não folha, e criando sua primeira chave.
        page->pai->folha = 0;
        page->pai->chaves[0] = (chave*)malloc(sizeof(chave));
        if(!page->pai->chaves[0]){
            free(page->pai);
            return 0;
        }
        page->pai->chaves[0]->chave = valor;
        page->pai->chaves[0]->indice = indice;
        //Criando seus dois filhos.
        page->pai->filhos = (pagina**)malloc(sizeof(pagina*) * arv->ordem);
        if(!page->pai->filhos){
            free(page->pai->chaves[0]);
            free(page->pai);
            return 0;
        }
        page->pai->filhos[0] = page;
        for(int i = 1; i <= arv->ordem; i++){
            page->pai->filhos[i] = NULL;
        }
        if(!divideIrmao(arv, page->pai, 0, 1)){
            return 0;
        }
        //Setando a nova raiz.
        arv->raiz = page->pai;
    }
    return 1;
}

/*
Descrição: Função que recebe uma página pai, e os indices das páginas filhas que serão divididas. A função olha qual dos filhos é nulo, e joga metade
    dos elementos da outra página para essa nula. Aqui tem 2 casos, se a página original é da esquerda, nós pegamos a metade direita e jogamos para a
    metade esquerda da página direita. Mas se a página original for da direita, nós pegamos a metade esquerda e jogamos para a metade esquerda da
    página esquerda, e pegamos os elementos da metade direita da página original e jogamos na sua metade esquerda.
Entrada: Ponteiro para a árvore, ponteiro para a página pai, indice do irmão esquerdo, indice do irmão direito.
Saída: 1 - Sucesso, 0 - Erro.
*/
int divideIrmao(arvore *arv, pagina *pai, int irmaoEsq, int irmaoDir){
    int final = arv->ordem, metade = 0;
    if(arv->ordem % 2 == 0){
        final = arv->ordem - 1;
        metade = -1;
    }
    //Verificando qual é o elemento nulo.
    if(!pai->filhos[irmaoEsq]){
        //Filho esquerdo é o nulo.
        //Criando página para o filho esquerdo.
        pai->filhos[irmaoEsq] = criaPagina(arv);
        if(!pai->filhos[irmaoEsq]){
            return 0;
        }
        //Setando seu pai.
        pai->filhos[irmaoEsq]->pai = pai;
        //Jogando os elementos da esquerda do outro irmão para a esquerda dessa página, e arrumando o irmão.
        for(int i = arv->ordem/2 - metade, j = 0; i < final; i++, j++){
            pai->filhos[irmaoEsq]->chaves[j] = (chave*)malloc(sizeof(chave));
            if(!pai->filhos[irmaoEsq]->chaves[j]){
                free(pai->filhos[irmaoEsq]);
                return 0;
            }
            pai->filhos[irmaoEsq]->chaves[j]->chave = pai->filhos[irmaoDir]->chaves[j]->chave;
            pai->filhos[irmaoEsq]->chaves[j]->indice = pai->filhos[irmaoDir]->chaves[j]->indice;
            pai->filhos[irmaoEsq]->nChaves += 1;
            pai->filhos[irmaoDir]->chaves[j]->chave = pai->filhos[irmaoDir]->chaves[i]->chave;
            pai->filhos[irmaoDir]->chaves[j]->indice = pai->filhos[irmaoDir]->chaves[i]->indice;
            free(pai->filhos[irmaoDir]->chaves[i]);
            pai->filhos[irmaoDir]->chaves[i] = NULL;
            pai->filhos[irmaoDir]->nChaves -= 1;
        }
    }else if(!pai->filhos[irmaoDir]){
        //Filho direito é o nulo.
        //Criando página para o filho direito.
        pai->filhos[irmaoDir] = criaPagina(arv);
        if(!pai->filhos[irmaoDir]){
            return 0;
        }
        //Setando seu pai.
        pai->filhos[irmaoDir]->pai = pai;
        //Jogando os elementos da direita do outro irmão para a esquerda dessa página.
        for(int i = arv->ordem/2 - metade, j = 0; i < final; i++, j++){
            pai->filhos[irmaoDir]->chaves[j] = (chave*)malloc(sizeof(chave));
            if(!pai->filhos[irmaoDir]->chaves[j]){
                free(pai->filhos[irmaoDir]);
                return 0;
            }
            pai->filhos[irmaoDir]->chaves[j]->chave = pai->filhos[irmaoEsq]->chaves[i]->chave;
            pai->filhos[irmaoDir]->chaves[j]->indice = pai->filhos[irmaoEsq]->chaves[i]->indice;
            pai->filhos[irmaoDir]->nChaves += 1;
            free(pai->filhos[irmaoEsq]->chaves[i]);
            pai->filhos[irmaoEsq]->chaves[i] = NULL;
            pai->filhos[irmaoEsq]->nChaves -= 1;
        }
    }
    return 1;
}
