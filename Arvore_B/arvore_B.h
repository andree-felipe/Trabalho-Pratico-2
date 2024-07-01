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
void merge(pagina *page, arvore *arv, int pos);

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
pagina *buscaChave(pagina *pagina, int chave);

/*
Descrição: Função auxiliar para buscar a posição de um elemento na página.
Entrada: Ponteiro para página e a chave a ser buscada.
Saída: Posição para a chave procurada.
*/
int buscaPos(pagina *pagina, int chave);

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


pagina *getRaiz(arvore *arv);

/*
Descrição: Função que remove a chave especificada da ávore B.
Entrada: Ponteiro para a árvore b, inteiro da chave.
Saída: 1 - Sucesso, 0 - Erro.
*/
int removeChave(arvore *arv, int chave);