#include "arvore_B.h"
#include <stdlib.h>
#include <stdio.h>

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

pagina *getRaiz(arvore *arv){
    return arv->raiz;
}

int getNumElementos(arvore *arv){
    return arv->numElementos;
}

int getOrdem(arvore *arv){
    return arv->ordem;
}

pagina *criaRaiz(arvore *arv, chave *valor, pagina *filho){
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
    raiz->chaves[0] = valor;
    raiz->nChaves = 1;
    raiz->filhos[0] = arv->raiz;
    if(raiz->filhos[0]){
        raiz->filhos[0]->pai = raiz;
    }
    raiz->filhos[1] = filho;
    if(raiz->filhos[1]){
        raiz->filhos[1]->pai = raiz;
    }
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

pagina *criaPagina(int quantidade){
    //Criando página.
    pagina *newPage = (pagina*)malloc(sizeof(pagina));
    if(!newPage){
        return NULL;
    }
    //Alocando espaço para seus ponteiros de ponteiros.
    newPage->chaves = (chave**)malloc(sizeof(chave*) * (quantidade));
    if(!newPage->chaves){
        free(newPage);
        return NULL;
    }
    newPage->filhos = (pagina**)malloc(sizeof(pagina*) * (quantidade + 1));
    if(!newPage->filhos){
        free(newPage->chaves);
        free(newPage);
        return NULL;
    }
    //Inicializando tudo como nulo.
    for(int i = 0; i < quantidade; i++){
        newPage->chaves[i] = NULL;
        newPage->filhos[i] = NULL;
    }
    newPage->filhos[quantidade] = NULL;
    return newPage;
}

int insere(arvore *arv, int matricula, int indice) {
    int cond; //Verifica se a árvore está cheia, e necessita de uma nova raiz.
    chave *registro = (chave*)malloc(sizeof(chave)); //Aloca um novo bloco para o registro.
    chave **inserida = NULL; //Essa função aponta para o registro que será inserido.
    pagina *filho; //Representa o filho da página atual, é setado na insereChave.
    if(!registro){
        return 0;
    }
    //Salvando os dados no registro.
    registro->chave = matricula;
    registro->indice = indice;
    //Chamando a função responsável por identificar o que fazer com o novo elemento.
    cond = insereChave(arv, inserida, registro, arv->raiz, &filho);
    if(cond) { //Significa que a árvore está cheia
        //Cria uma nova raiz
        arv->raiz = criaRaiz(arv, *inserida, filho);
        if(!arv->raiz)
            return 0;
    }
    return 1;
}

void inserePagina(pagina *page, pagina *filho, chave *registro, int pos){
    for(int i = page->nChaves; i != pos; i--){
        page->chaves[i] = page->chaves[i - 1];
        page->filhos[i+1] = page->filhos[i];
    }
    page->chaves[pos] = registro;
    page->filhos[pos + 1] = filho;
    if(page->filhos[pos + 1]){
        //Utilizado quando o split é em um nó intermediário, pois esse filho está vinculado com o nó original (antes do split).
        page->filhos[pos + 1]->pai = page;
    }
    page->nChaves++;
}

int insereChave(arvore *arv, chave **inserida, chave *registro, pagina *page, pagina **filho){
    int pos; //Representa o filho na qual a chave entra.
    if(!page){
        //Se a página for nula, chegamos a uma folha.
        *inserida = registro; //Fazendo o ponteiro de ponteiro apontar para o registro inicial.
        *filho = NULL; //Setando como nulo, pois não tem filho.
        return 1;
    }
    //Procurando em qual filho/posição entra a chave.
    for(pos = 0; pos < page->nChaves && registro->chave > page->chaves[pos]->chave; pos++);
    //Se a recursiva desse função, com o filho[pos], for 0 a execução acaba, se for 1 insere ou da split.
    if(insereChave(arv, inserida, registro, page->filhos[pos], filho)){
        //Se tem espaço na página, insere o registro, se não tem espaço da split.
        if(page->nChaves < arv->ordem - 1){
            inserePagina(page, *filho, *inserida, pos);
        }else{
            if(split(inserida, *inserida, page, *filho, filho, pos)){
                return 1;
            }
        }
    }
    return 0;
}

int split(chave **inserida, chave *registro, pagina *page, pagina *filho, pagina **newPage, int pos) {
    int mediana=page->nChaves / 2; //Número de chaves sempre vai ser ímpar, logo a metade é o inteiro resultante da divisão por 2.
    //Cria a nova página para realizar a divisão dos elementos, e cria espaço para seus ponteiros de ponteiros.
    *newPage = criaPagina(page->nChaves);
    if(!*newPage){
        return 0;
    }
    (*newPage)->folha = page->folha;
    (*newPage)->pai = page->pai;

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
        inserePagina(page, filho, registro, pos);
    else
        //Nova página criada
        inserePagina(*newPage, filho, registro, pos - mediana - 1);

    //A chave que vai subir para o pai é a chave na posição da mediana na página analisada, aqui fazemos o nosso ponteiro de ponteiro apontar
    // para essa chave.
    *inserida = page->chaves[page->nChaves-1];
    //Chave mediana removida da página analisada.
    page->nChaves--;
    page->chaves[page->nChaves] = NULL;
    return 1;
}

void imprimeArvore(pagina *raiz, int nivel){
    if(raiz){
        printf("\n%d - %d - ", nivel, raiz->nChaves);
        for(int i = 0; i < raiz->nChaves; i++){
            printf("%d ", raiz->chaves[i]->chave);
        }
        if(raiz->pai){
            printf("- %d", raiz->pai->chaves[0]->chave);
        }
        for(int i = 0; i <= raiz->nChaves; i++){
            imprimeArvore(raiz->filhos[i], nivel + 1);
        }
    }
}
