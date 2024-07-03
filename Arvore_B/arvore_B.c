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
Descrição: Retorna a quantidade de elementos da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Inteiro da quantidade de elementos da árvore.
*/
int getNumElementos(arvore *arv){
    return arv->numElementos;
}

/*
Descrição: Retorna a ordem da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Inteiro da ordem.
*/
int getOrdem(arvore *arv){
    return arv->ordem;
}

/*
Descrição: Cria uma estrutura de página para a raiz.
Entrada: Ponteiro para a árvore b, estrutura com os valores iniciais, ponteiro para uma página filha.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaRaiz(arvore *arv, chave *valor, pagina *filho){
    //Criando a raiz.
    pagina *raiz = (pagina*)malloc(sizeof(pagina));
    if(!raiz){
        return NULL;
    }
    //Criando espaço para as chaves e os filhos.
    raiz->chaves = (chave**)malloc(sizeof(chave*) * (arv->ordem - 1));
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

/*
Descrição: Função responsável por criar uma nova página para o split (por enquanto só aceita ordem par).
Entrada: Quantidade de chaves (arv->ordem - 1).
Saída: Ponteiro para a nova página;
*/
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

/*
Descrição: Função de inserção de um elemento na árvore. Aloca um bloco para guardar o registro e passa o ponteiro dele para a insereChave,
    também cria um ponteiro de ponteiro que sempre irá apontar para o novo bloco de registro que será incluído, dessa forma durante a split ele
    começa a apontar para o bloco que subiu.
Entrada: Ponteiro para a raiz da árvore, inteiro da matrícula (chave principal), inteiro do índice (linha no arquivo).
Saída: 1 - Sucesso, 0 - Casos de erro.
*/
int insere(arvore *arv, int matricula, int indice) {
    int cond; //Verifica se a árvore está cheia, e necessita de uma nova raiz.
    chave *registro = (chave*)malloc(sizeof(chave)); //Aloca um novo bloco para o registro.
    chave **inserida = &registro; //Essa função aponta para o registro que será inserido.
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
    arv->numElementos++;
    return 1;
}

/*
Descrição: Função que insere um registro em uma página.
Entrada: Ponteiro para a página, ponteiro para o filho do registro, ponteiro para o registro, inteiro da posição onde o registro entra.
Saída: Nada.
*/
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

/*
Descrição: Função que procura em qual filho vai o registro, se for folha significa que achou a posição dele na chave. E faz isso recursivamente,
    decidindo se vai inserir, dar split, ou não fazer nada.
Entrada: Ponteiro para a árvore b, ponteiro de ponteiro para o registro que será inserido (será alterado na split), ponteiro para o registro, ponteiro
    para a página atual, ponteiro de ponteiro para o filho (usada para guardar a nova página da split na estrutura criada na insere).
Saída: 1 - ou insere, ou da split, ou cria uma nova raiz (são tratados nas funções), 0 - Encerra a execução.
*/
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

/*
Descrição: Função para corrigir o balanceamento da árvore, realizando a subdivisão da página cheia em duas novas páginas.
Entrada: Ponteiro de ponteiro para o registro que será inserido, ponteiro para o registro, ponteiro para a página cheia, ponteiro para o filho,
    ponteiro de ponteiros para a nova página (novo filho), inteiro da posição.
Saída: 1 - Sucesso, 0 - Casos de erro
*/
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

/*
Descrição: Função que busca em qual página está a matrícula informada, se ela encontrar salva a posição da chave.
Entrada: Ponteiro para a raiz, inteiro da matrícula.
Saída: -1 - Elemento não encontrada, caso contrário é o índice do elemento no arquivo.
*/
int buscaChave(pagina *raiz, int mat){
    pagina *aux, *atual = raiz;
    int pos = -1;
    //Iniciando a busca pela página.
    while(atual){
        aux = atual;
        for(int i = 0; atual && i < atual->nChaves && aux == atual; i++){
            if(mat < atual->chaves[i]->chave){
                //Elemento está no filho esquerdo da chave.
                atual = atual->filhos[i];
            }else if(mat == atual->chaves[i]->chave){
                //Elemento encontrado, encerrando o loop e salvando a posição.
                pos = i;
                atual = NULL;
            }else if(i == atual->nChaves - 1){
                //Elemento está no filho mais a direita.
                atual = atual->filhos[i+1];
            }
        }
        if(pos != -1){
            return aux->chaves[pos]->indice;
        }
    }
    return -1;
}

/*
Descrição: Função que imprime a árvore da seguinte maneira: nível - número de chaves - chaves - pai (se tiver). A função é chamada recursivamente
    imprimindo as sub-árvores da esquerda para a direita.
Entrada: Ponteiro para a página (raiz inicialmente), inteiro do nível (0 inicialmente).
Saída: Nada.
*/
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

/*
Descrição: Função que irá ler o arquivo de entrada e com base neles, gerar a árvore b.
Entrada: Ponteiro para a árvore b, ponteiro para o arquivo.
Saída: 1 - Sucesso, 0 - Erro.
*/
int processaEntrada(arvore *arv, FILE *arq){
    int indice = 0, mat;
    long int cpf;
    char nome[6], data[11];
    while(!feof(arq)){
        fscanf(arq, "%d %s %s %ld", &mat, nome, data, &cpf);
        if(!insere(arv, mat, indice++)){
            return 0;
        }
    }
    return 1;
}

/*
Descrição: Função que libera a memória alocada para uma página.
Entrada: Página que irá ser liberada.
Saída: Nada.
*/
void deletaPagina(pagina *page){
    free(page->chaves);
    free(page->filhos);
    free(page);
}

/*
Descrição: Função que procura o predecessor da página, e copía ele para a posição informada.
Entrada: Ponteiro para a página que irá receber o predecessor, inteiro da posição onde o predecessor será copiado.
Saída: Nada.
*/
void copiaPredecessor(pagina *page, int pos){
    pagina *filho = page->filhos[pos]; //Pegando o filho da esquerda (elementos menores do que a chave).
    //Enquanto o filho não for folha, vamos para a sub-árvore mais a direita.
    while(!filho->folha){
        filho = filho->filhos[filho->nChaves];
    }
    //Fazendo a cópia para a posição informada.
    page->chaves[pos]->chave = filho->chaves[filho->nChaves-1]->chave;
    page->chaves[pos]->indice = filho->chaves[filho->nChaves-1]->indice;
}

/*
Descrição: Função que remove o elemento indicado na página informada.
Entrada: Ponteiro para a página folha onde o elemento será removido, inteiro da posição onde está o elemento.
Saída: Nada.
*/
void removeChave(pagina *page, int pos){
    chave *aux = page->chaves[pos]; //Salvando o bloco que será removido, para liberar depois.
    //Fazendo com que todos os elementos à direita da posição, deem um shift para a esquerda.
    for(int i = pos; i < page->nChaves - 1; i++){
        page->chaves[i] = page->chaves[i + 1];
    }
    //Setando a última chave como nula.
    page->chaves[page->nChaves - 1] = NULL;
    //Liberando o bloco, e setando o novo tamanho da folha.
    free(aux);
    page->nChaves--;
}

/*
Descrição: Função que realiza o processo de rotação para a esquerda na página.
Entrada: Ponteiro para a página pai, inteiro indicando qual filho receberá o novo elemento.
Saída: Nada.
*/
void emprestaDireita(pagina *page, int pos){
    pagina *filhoD = page->filhos[pos + 1], *filhoE = page->filhos[pos];
    //Filho esquerdo recebe o pai, e recebe um novo filho da sua página irmã.
    filhoE->chaves[filhoE->nChaves] = page->chaves[pos];
    filhoE->filhos[filhoE->nChaves + 1] = filhoD->filhos[0];
    if(filhoD->filhos[0]){
        filhoD->filhos[0]->pai = filhoE;
    }
    filhoE->nChaves++;
    //Pai recebe a primeira chave do filho direito.
    page->chaves[pos] = filhoD->chaves[0];
    filhoD->nChaves--;
    //Fazendo os elementos restantes do filho direito darem um shift para a esquerda.
    for(int i = 0; i < filhoD->nChaves; i++){
        filhoD->chaves[i] = filhoD->chaves[i+1];
        filhoD->filhos[i] = filhoD->filhos[i+1];
    }
    filhoD->filhos[filhoD->nChaves] = filhoD->filhos[filhoD->nChaves + 1];
    //Setando as últimas posições como nulo.
    filhoD->chaves[filhoD->nChaves] = NULL;
    filhoD->filhos[filhoD->nChaves + 1] = NULL;
}

/*
Descrição: Função que realiza o processo de rotação para a direita na página.
Entrada: Ponteiro para a página pai, inteiro indicando o filho direito.
Saída: Nada.
*/
void emprestaEsquerda(pagina *page, int pos){
    pagina *filhoD = page->filhos[pos], *filhoE = page->filhos[pos - 1];
    //Fazendo os elementos do filho da direita abrirem espaço para o pai descer.
    for(int i = filhoD->nChaves; i > 0; i--){
        filhoD->chaves[i] = filhoD->chaves[i - 1];
        filhoD->filhos[i+1] = filhoD->filhos[i];
    }
    filhoD->filhos[1] = filhoD->filhos[0];
    //Elemento inicial do filho direito recebe o pai, e um novo filho da sua página irmã.
    filhoD->chaves[0] = page->chaves[pos-1];
    filhoD->filhos[0] = filhoE->filhos[filhoE->nChaves];
    if(filhoE->filhos[filhoE->nChaves]){
        filhoE->filhos[filhoE->nChaves]->pai = filhoD;
    }
    filhoD->nChaves++;
    //Pai recebe a última chave do filho esquerdo.
    page->chaves[pos-1] = filhoE->chaves[filhoE->nChaves-1];
    filhoE->chaves[filhoE->nChaves - 1] = NULL;
    filhoE->filhos[filhoE->nChaves] = NULL;
    filhoE->nChaves--;
}

/*
Descrição: Função que recebe a página pai, e mescla o filho da direita com o esquerdo. (Os elementos vão da direita para a esquerda).
Entrada: Ponteiro para página pai, inteiro indicando o filho direito.
Saída: Nada.
*/
void merge(pagina *page, int pos){
    pagina *filhoE = page->filhos[pos-1], *filhoD = page->filhos[pos];
    //Filho esquerdo recebe o pai correspondente, e um novo filho da sua página irmã.
    filhoE->chaves[filhoE->nChaves] = page->chaves[pos-1];
    filhoE->filhos[filhoE->nChaves+1] = filhoD->filhos[0];
    filhoE->nChaves++;
    //Filho esquerdo recebe os elementos da página irmã.
    for(int i = 0; i < filhoD->nChaves; i++){
        filhoE->chaves[filhoE->nChaves] = filhoD->chaves[i];
        filhoE->filhos[filhoE->nChaves+1] = filhoD->filhos[i+1];
        filhoE->nChaves++;
    }
    //Fazendo os elementos na página pai darem um shift para a esquerda.
    for(int i = pos - 1; i < page->nChaves - 1; i++){
        page->chaves[i] = page->chaves[i+1];
        page->filhos[i+1] = page->filhos[i+2];
    }
    page->chaves[page->nChaves-1] = NULL;
    page->filhos[page->nChaves] = NULL;
    page->nChaves--;
    //Vinculando todos os filhos da página irmã com o novo pai.
    if(!filhoD->folha){
        for(int i = 0; i <= filhoD->nChaves; i++){
            filhoD->filhos[i]->pai = filhoE;
        }
    }
    //Liberando a página irmã.
    deletaPagina(filhoD);
}

/*
Descrição: Função responsável por determinar qual dos métodos chamar para corrigir os filhos.
Entrada: Ponteiro para a árvore (para ter acesso à ordem), ponteiro para a página pai, inteiro indicando a página filha que está com elementos abaixo do mínimo.
Saída: Nada.
*/
void corrigiFilho(arvore *arv, pagina *page, int pos){
    //Se o filho está na esquerda, o único empréstimo possível é da página irmã da direita.
    if(pos == 0){
        if(page->filhos[pos + 1]->nChaves > (arv->ordem/2) - 1){
            //Página irmã consegue perder um elemento.
            emprestaDireita(page, pos);
        }else{
            //Página irmã não consegue perder um elemento, unificando as duas.
            merge(page, 1);
        }
    }else{
        //Se o filho estiver na direita, o único empréstimo possível é da página irmã da esquerda.
        if(pos == page->nChaves){
            if(page->filhos[pos - 1]->nChaves > (arv->ordem/2) - 1){
                //Página irmã consegue perder um elemento.
                emprestaEsquerda(page, pos);
            }else{
                //Página irmã não consegue perder um elemento, unificando as duas.
                merge(page, pos);
            }
        //Elemento está em uma página intermediária.
        }else{
            if(page->filhos[pos + 1]->nChaves > (arv->ordem/2) - 1){
                //Página irmã da direita consegue perder um elemento.
                emprestaDireita(page, pos);
            }else if(page->filhos[pos - 1]->nChaves > (arv->ordem/2) - 1){
                //Página irmã da esquerda consegue perder um elemento.
                emprestaEsquerda(page, pos);
            }else{
                //Nenhuma das páginas irmãs conseguem perder um elemento, unificando com a página irmã da esquerda.
                merge(page, pos);
            }
        }
    }
}

/*
Descrição: Função recursiva, responsável por procurar em qual filho está a chave ou em qual posição está chave.
Entrada: Ponteiro para a árvore, ponteiro para a página, inteiro que será removido.
Saída: 1 - Elemento encontrado e removido, 0 - Elemento não encontrado.
*/
int deletaDaPagina(arvore *arv, pagina *page, int mat) {
    int pos, cond = 0;
    if (page) {
        //Procurando onde está a matrícula.
        for(pos = 0; pos < page->nChaves && mat > page->chaves[pos]->chave; pos++);
        //Verificando se a matrícula está na página atual.
        if(pos < page->nChaves && mat == page->chaves[pos]->chave){
            cond = 1;
        }
        //Se a matrícula estiver na página atual, removemos fazendo as verificações necessárias, se não estiver chamamos a essa mesma função recursivamente com o filho.
        if (cond) {
            //Se a página atual não for folha, copiamos o predecessor para o elemento atual, e removemos o com a chamada recursiva dessa função.
            if (!page->folha) {
                copiaPredecessor(page, pos);
                cond = deletaDaPagina(arv, page->filhos[pos], page->chaves[pos]->chave);
            //Página é folha, removendo elemento.
            } else {
                removeChave(page, pos);
                arv->numElementos--;
            }
        } else {
            //Elemento não está na página atual, verificando na página filha.
            cond = deletaDaPagina(arv, page->filhos[pos], mat);
        }
        //Caso o filho onde foi removido um elemento estiver com um número de chaves menor do que o mínimo, devemos ajustar esse filho.
        if (!page->folha) {
            if (page->filhos[pos]->nChaves < (arv->ordem/2) - 1){
                corrigiFilho(arv, page, pos);
            }
        }
    }
    return cond;
}

/*
Descrição: Função responsável por verificar se a árvore está vazia, e por tratar os retornos da função deletaDaPagina.
Entrada: Ponteiro para a árvore, inteiro que será removido.
Saída: 1 - Sucesso, 0 - Elemento não encontrado, -1 - Árvore vazia.
*/
int deleta(arvore *arv, int mat){
    pagina *aux, *raiz = arv->raiz;
    //Verificando se a árvore está vazia.
    if(arv->numElementos > 0){
        //Se a função retornar 0, o elemento não foi encontrado.
        if(!deletaDaPagina(arv, raiz, mat)){
            return 0;
        //Elemento encontrado e removido.
        }else{
            //Se a raiz atual possui 0 elementos, a altura da árvore diminuiu, e a raiz foi mesclada com o filho esquerdo.
            if(raiz->nChaves == 0){
                aux = raiz;
                raiz = raiz->filhos[0];
                if(raiz){
                    raiz->pai = NULL;
                }
                deletaPagina(aux);
                aux = NULL;
            }
        }
        arv->raiz = raiz;
        return 1;
    }
    return -1;
}
