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
Descrição:
Entrada:
Saída: 
*/
pagina *criaRaiz(arvore *arv, chave registro, pagina *filho);

/*
Descrição:
Entrada:
Saída: 
*/
int insere(arvore *arv, chave registro);

/*
Descrição:
Entrada:
Saída: 
*/
int inserePagina(pagina *page, pagina *filho, chave registro, int pos);

/*
Descrição:
Entrada:
Saída: 
*/
int insereChave(chave registro, chave *pontReg, pagina *page, pagina **filho);

/*
Descrição:
Entrada:
Saída:
*/
void split(chave registro, chave *pontReg, pagina *page, pagina *filho, pagina **newPage, int pos);

#endif //INC_13_TRABALHO2_ARVORE_B_H
