#ifndef INC_13_TRABALHO2_ARVORE_B_H
#define INC_13_TRABALHO2_ARVORE_B_H

/*** -- Estruturas -- ***/

typedef struct pagina pagina;

typedef struct chave chave;

typedef struct arvore arvore;

/*** -- Funções -- ***/

/*
Descrição: Função para reorganizar a árvore por merge dos irmãos.
Entrada: Ponteiro para página, ponteiro para árvore e 
Saída: Ponteiro para a maior chave da subárvore esquerda.
*/
void merge(pagina *page, arvore *arv, int idx);

/*
Descrição: Função para encontrar a maior chave na subárvore esquerda.
Entrada: Ponteiro para página
Saída: Ponteiro para a maior chave da subárvore esquerda.
*/
chave *encontraAntecessor(pagina *pagina);

/*
Descrição: Função auxiliar para buscar o índice de uma página.
Entrada: Ponteiro para página e a chave a ser buscada.
Saída: Índice para a chave procurada.
*/
int buscaChave(pagina *pagina, int chave);

/*
Descrição: Função auxiliar para buscar a posição de um elemento na página.
Entrada: Ponteiro para página e a chave a ser buscada.
Saída: Posição para a chave procurada.
*/
int buscaIdx(pagina *pagina, int chave);

/*
Descrição: Função para remover chave de folha.
Entrada: Ponteiro para página e a chave a ser removida.
Saída: Void.
*/
void removeDeFolha(pagina *page, int indice);

/*
Descrição: Função para remover chave de não folha.
Entrada: Ponteiro para página e a chave a ser removida.
Saída: Void.
*/
void removeDeNaoFolha(pagina *page, int i);

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
Descrição: Cria uma estrutura da página.
Entrada: Ponteiro para a árvore b.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaPagina(arvore *arv);

/*
Descrição: Insere um elemento na árvore, e chama as funções de correção dependendo do caso.
Entrada: Ponteiro para a árvore b, inteiro da chave, inteiro da linha.
Saída: 1 - Sucesso, 0 - Erro.
*/
int insereNo(arvore *arv, int chave, int indice);



#endif //INC_13_TRABALHO2_ARVORE_B_H