#ifndef INC_13_TRABALHO2_ARVORE_B_H
#define INC_13_TRABALHO2_ARVORE_B_H

/*** -- Estruturas -- ***/

typedef struct pagina pagina;

typedef struct chave chave;

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
Descrição: Função de inserção de um elemento na árvore. Aloca um bloco para guardar o registro e passa o ponteiro dele para a insereChave ou criaRaiz,
    esse ponteiro pode apontar para outros blocos durante a execução da insereChave, mas isso significa que o bloco original já está salvo por outro
    ponteiro, e isso só acontecerá se um split ocorrer.
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
Descrição: Função recursiva que encontra em qual filho está o novo registro, até chegar em uma folha. Quando chegar na folha, verifica
    se há espaço, se houver insere nela, se não houver divide o nó e recursivamente vincula com o pai.
Entrada: Ponteiro para a árvore b, ponteiro para o registro (será alterado na split), ponteiro para a página atual,
    ponteiro de ponteiro para o filho (usada para guardar a nova página da split na estrutura criada na insere).
Saída: 1 - ou insere, ou da split, ou cria uma nova raiz (são tratados nas funções), 0 - Encerra a execução.
*/
int insereChave(arvore *arv, chave *registro, pagina *page, pagina **filho);

/*
Descrição: Função para corrigir o balanceamento da árvore, realizando a subdivisão da página cheia em duas novas páginas.
Entrada: Ponteiro para o registro, ponteiro para a página cheia, ponteiro para o filho, ponteiro de ponteiros para a nova página (novo filho),
    inteiro da posição.
Saída: 1 - Sucesso, 0 - Casos de erro
*/
int split(chave *registro, pagina *page, pagina *filho, pagina **newPage, int pos);

#endif //INC_13_TRABALHO2_ARVORE_B_H
