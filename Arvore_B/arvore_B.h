#include <stdio.h>

/*** -- Estruturas -- ***/

typedef struct chave chave;

typedef struct pagina pagina;

typedef struct arvore arvore;

/*** -- Funções -- ***/

/*
Descrição: Cria uma estrutura da árvore b.
Entrada: Inteiro da ordem da árvore.
Saída: Ponteiro para a árvore; NULL em caso de erro.
*/
arvore *criaArvore(int ordem);

/*
Descrição: Retorna a raiz da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Ponteiro para a raiz da árvore.
*/
pagina *getRaiz(arvore *arv);

/*
Descrição: Retorna a quantidade de elementos da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Inteiro da quantidade de elementos da árvore.
*/
int getNumElementos(arvore *arv);

/*
Descrição: Retorna a ordem da árvore.
Entrada: Ponteiro para a árvore b.
Saída: Inteiro da ordem.
*/
int getOrdem(arvore *arv);

/*
Descrição: Cria uma estrutura de página para a raiz.
Entrada: Ponteiro para a árvore b, estrutura com os valores iniciais, ponteiro para uma página filha.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaRaiz(arvore *arv, chave *registro, pagina *filho);

/*
Descrição: Função responsável por criar uma nova página para o split (por enquanto só aceita ordem par).
Entrada: Quantidade de chaves (arv->ordem - 1).
Saída: Ponteiro para a nova página;
*/
pagina *criaPagina(int quantidade);

/*
Descrição: Função de inserção de um elemento na árvore. Aloca um bloco para guardar o registro e passa o ponteiro dele para a insereChave,
    também cria um ponteiro de ponteiro que sempre irá apontar para o novo bloco de registro que será incluído, dessa forma durante a split ele
    começa a apontar para o bloco que subiu.
Entrada: Ponteiro para a raiz da árvore, inteiro da matrícula (chave principal), inteiro do índice (linha no arquivo).
Saída: 1 - Sucesso, 0 - Casos de erro.
*/
int insere(arvore *arv, int matricula, int indice);

/*
Descrição: Função que insere um registro em uma página.
Entrada: Ponteiro para a página, ponteiro para o filho do registro, ponteiro para o registro, inteiro da posição onde o registro entra.
Saída: Nada.
*/
void inserePagina(pagina *page, pagina *filho, chave *registro, int pos);

/*
Descrição: Função que procura em qual filho vai o registro, se for folha significa que achou a posição dele na chave. E faz isso recursivamente,
    decidindo se vai inserir, dar split, ou não fazer nada.
Entrada: Ponteiro para a árvore b, ponteiro de ponteiro para o registro que será inserido (será alterado na split), ponteiro para o registro, ponteiro
    para a página atual, ponteiro de ponteiro para o filho (usada para guardar a nova página da split na estrutura criada na insere).
Saída: 1 - ou insere, ou da split, ou cria uma nova raiz (são tratados nas funções), 0 - Encerra a execução.
*/
int insereChave(arvore *arv, chave **inserida, chave *registro, pagina *page, pagina **filho);

/*
Descrição: Função para corrigir o balanceamento da árvore, realizando a subdivisão da página cheia em duas novas páginas.
Entrada: Ponteiro de ponteiro para o registro que será inserido, ponteiro para o registro, ponteiro para a página cheia, ponteiro para o filho,
    ponteiro de ponteiros para a nova página (novo filho), inteiro da posição.
Saída: 1 - Sucesso, 0 - Casos de erro
*/
int split(chave **inserida, chave *registro, pagina *page, pagina *filho, pagina **newPage, int pos);

/*
Descrição: Função que busca em qual página está a matrícula informada, se ela encontrar salva a posição da chave.
Entrada: Ponteiro para a raiz, inteiro da matrícula.
Saída: -1 - Elemento não encontrada, caso contrário é o índice do elemento no arquivo.
*/
int buscaChave(pagina *raiz, int mat);

/*
Descrição: Função que imprime a árvore da seguinte maneira: nível - número de chaves - chaves - pai (se tiver). A função é chamada recursivamente
    imprimindo as sub-árvores da esquerda para a direita.
Entrada: Ponteiro para a página (raiz inicialmente), inteiro do nível (0 inicialmente).
Saída: Nada.
*/
void imprimeArvore(pagina *raiz, int nivel);

/*
Descrição: Função que irá ler o arquivo de entrada e com base neles, gerar a árvore b.
Entrada: Ponteiro para a árvore b, ponteiro do arquivo.
Saída: 1 - Sucesso, 0 - Erro.
*/
int processaEntrada(arvore *arv, FILE *arq);

/*
Descrição: Função que libera a memória alocada para uma página.
Entrada: Página que irá ser liberada.
Saída: Nada.
*/
void deletaPagina(pagina *page);

/*
Descrição: Função que procura o predecessor da página, e copía ele para a posição informada.
Entrada: Ponteiro para a página que irá receber o predecessor, inteiro da posição onde o predecessor será copiado.
Saída: Nada.
*/
void copiaPredecessor(pagina *page, int pos);

/*
Descrição: Função que remove o elemento indicado na página informada.
Entrada: Ponteiro para a página folha onde o elemento será removido, inteiro da posição onde está o elemento.
Saída: Nada.
*/
void removeChave(pagina *page, int pos);

/*
Descrição: Função que realiza o processo de rotação para a esquerda na página.
Entrada: Ponteiro para a página pai, inteiro indicando qual filho receberá o novo elemento.
Saída: Nada.
*/
void emprestaDireita(pagina *page, int pos);

/*
Descrição: Função que realiza o processo de rotação para a direita na página.
Entrada: Ponteiro para a página pai, inteiro indicando o filho direito.
Saída: Nada.
*/
void emprestaEsquerda(pagina *page, int pos);

/*
Descrição: Função que recebe a página pai, e mescla o filho da direita com o esquerdo. (Os elementos vão da direita para a esquerda).
Entrada: Ponteiro para página pai, inteiro indicando o filho direito.
Saída: Nada.
*/
void merge(pagina *page, int pos);

/*
Descrição: Função responsável por determinar qual dos métodos chamar para corrigir os filhos.
Entrada: Ponteiro para a árvore (para ter acesso à ordem), ponteiro para a página pai, inteiro indicando a página filha que está com elementos abaixo do mínimo.
Saída: Nada.
*/
void corrigiFilho(arvore *arv, pagina *page, int pos);

/*
Descrição: Função recursiva, responsável por procurar em qual filho está a chave ou em qual posição está chave.
Entrada: Ponteiro para a árvore, ponteiro para a página, inteiro que será removido.
Saída: 1 - Elemento encontrado e removido, 0 - Elemento não encontrado.
*/
int deletaDaPagina(arvore *arv, pagina *page, int mat);

/*
Descrição: Função responsável por verificar se a árvore está vazia, e por tratar os retornos da função deletaDaPagina.
Entrada: Ponteiro para a árvore, inteiro que será removido.
Saída: 1 - Sucesso, 0 - Elemento não encontrado, -1 - Árvore vazia.
*/
int deleta(arvore *arv, int mat);
