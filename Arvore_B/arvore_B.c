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
Descrição: Cria uma estrutura de página para a raiz.
Entrada: Ponteiro para a árvore b, estrutura com os valores iniciais, ponteiro para uma página filha.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaRaiz(arvore *arv, chave valor, pagina *filho){
    //Criando a raiz.
    pagina *raiz = (pagina*)malloc(sizeof(pagina));
    if(!raiz){
        return NULL;
    }
    //Criando espaço para as chaves e os filhos.
    if(arv->ordem % 2 == 0){
        raiz->chaves = (chave**)malloc(sizeof(chave*) * (arv->ordem - 1));
    }else{
        raiz->chaves = (chave**)malloc(sizeof(chave*) * (arv->ordem));
    }
    if(!raiz->chaves){
        free(raiz);
        return NULL;
    }
    raiz->filhos = (pagina**)malloc(sizeof(pagina*) * (arv->ordem));
    if(!raiz->filhos){
        free(raiz->chaves);
        free(raiz);
        return NULL;
    }
    //Setando os elementos iniciais.
    if(filho){
        //Se o filho existe, não é folha.
        raiz->folha = 0;
    }else{
        //Se o filho não existe, é folha.
        raiz->folha = 1;
    }
    raiz->pai = NULL;
    raiz->chaves[0] = (chave*)malloc(sizeof(chave));
    if(!raiz->chaves[0]){
        free(raiz->filhos);
        free(raiz->chaves);
        free(raiz);
        return NULL;
    }
    raiz->chaves[0]->chave = valor.chave;
    raiz->chaves[0]->indice = valor.indice;
    raiz->nChaves = 1;
    raiz->filhos[0] = arv->raiz;
    raiz->filhos[1] = filho;
    //Setando o resto como nulo.
    raiz->chaves[1] = NULL;
    for(int i = 2; i < arv->ordem-1; i++){
        raiz->chaves[i] = NULL;
        raiz->filhos[i] = NULL;
    }
    raiz->filhos[arv->ordem - 1] = NULL;
    if(arv->ordem % 2 == 1){
        raiz->chaves[arv->ordem-1] = NULL;
    }
    return raiz;
}

/*
Descrição: Função para inserção no arquivo de índice.
Entrada: Ponteiro para a raiz da árvore, registro a ser inserido.
Saída: 1 - Sucesso, 0 - Casos de erro.
*/
int insere(arvore *arv, chave valor) {
    int cond;
    chave reg;
    pagina *filho;

    cond = insereChave(arv, valor, &reg, arv->raiz, &filho);
    if(cond) { //Significa que a árvore está cheia
        //Cria uma nova raiz
        arv->raiz = criaRaiz(arv, valor, filho);
        if(!arv->raiz)
            return 0;
    }
    return 1;
}

/*
Descrição: Função recursiva que encontra em qual filho está o novo registro, até chegar em uma folha. Quando chegar na folha, verifica
    se há espaço, se houver insere nela, se não houver divide o nó e recursivamente vincula com o pai.
Entrada: Ponteiro para a árvore b, estrutura com os valores, ponteiro para os valores (serão alterados na split), ponteiro para a página atual,
    ponteiro de ponteiro para o filho (usada para guardar o novo nó da split na estrutura criada na insere).
Saída: 1 - ou insere, ou da split, ou cria uma nova raiz (são tratados nas funções), 0 - encerra a execução.
*/
int insereChave(arvore *arv, chave registro, chave *pontReg, pagina *page, pagina **filho){
    int pos; //Representa o filho na qual a chave entra.
    if(!page){
        //Se a página for nula, chegamos a uma folha.
        *filho = NULL; //Setando como nulo, pois não tem filho.
        *pontReg = registro; //Salvando o próprio registro.
        return 1;
    }
    //Procurando em qual filho entra a chave.
    for(pos = 0; pos < page->nChaves && registro.chave > page->chaves[pos]->chave; pos++);
    //Se a recursiva desse função, com o filho[pos], for 0 a execução acaba, se for 1 insere ou da split.
    if(insereChave(arv, registro, pontReg, page->filhos[pos], filho)){
        //Se tem espaço na página, insere o registro, se não tem espaço da split.
        if(page->nChaves < arv->ordem - 1){
            inserePagina(page, *filho, registro, pos);
        }else{
            if(split(registro, pontReg, page, *filho, filho, pos)){
                return 1;
            }
        }
    }
    return 0;
}

/*
Descrição: Função para corrigir o balanceamento da árvore, realizando a subdivisão da página cheia em duas novas páginas
Entrada: A chave desejada, um endereço para a variável que irá guardar a chave mediana, a página cheia, a página filho,
         um endereço para o novo filho, a posição que será inserida a chave desejada
Saída: 1 - Sucesso, 0 - Casos de erro
*/
int split(chave valor, chave *pontReg, pagina *page, pagina *filho, pagina **newPage, int pos) {
    int mediana=page->nChaves / 2; //Número de chaves sempre vai ser ímpar, logo a metade é o inteiro resultante da divisão por 2.

    //Cria a nova página para realizar a divisão dos elementos, e cria espaço para seus ponteiros de ponteiros.
    *newPage = (pagina*)malloc(sizeof(pagina));
    if(!*newPage)
        return 0;
    (*newPage)->chaves = (chave**)malloc(page->nChaves * sizeof(chave*));
    if(!((*newPage)->chaves))
        return 0;
    (*newPage)->filhos = (pagina**)malloc((page->nChaves + 1) * sizeof(pagina*));
    if(!((*newPage)->filhos))
        return 0;
    //O certo seria deixar eles nulos, podemos criar uma função para criar essa página também.

    //Insere os elementos da parte direita da página cheia na nova página.
    for(int i=mediana+1; i<page->nChaves;i++) {
        (*newPage)->chaves[i - mediana - 1] = page->chaves[i];
        (*newPage)->filhos[i - mediana - 1] = page->filhos[i];
        if(page->filhos[i]){
            page->filhos[i]->pai = *newPage;
        }
        page->chaves[i] = NULL;
        page->filhos[i] = NULL;
    }
    (*newPage)->filhos[mediana] = page->filhos[page->nChaves];
    if(page->filhos[page->nChaves]){
        page->filhos[page->nChaves]->pai = *newPage;
    }
    page->filhos[page->nChaves] = NULL;

    //Atualiza as variáveis com as novas quantidades de chaves.
    (*newPage)->nChaves = mediana;
    page->nChaves -= mediana;

    //Procura onde deverá inserir o novo registro
    if(pos <= page->nChaves-1)
        //Página atual
        inserePagina(page, filho, valor, pos);
    else
        //Nova página criada
        inserePagina(*newPage, filho, valor, pos - mediana);

    //Guardando a chave mediana na variável "pontReg" para uso posterior
    (*pontReg).chave = page->chaves[page->nChaves-1]->chave;
    (*pontReg).indice = page->chaves[page->nChaves-1]->indice;
    //Chave mediana removida da página analisada
    page->nChaves--;
    page->chaves[page->nChaves] = NULL;
    return 1;
}
