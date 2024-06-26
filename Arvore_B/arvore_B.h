#ifndef INC_13_TRABALHO2_ARVORE_B_H
#define INC_13_TRABALHO2_ARVORE_B_H

/*** -- Estruturas -- ***/

typedef struct pagina pagina;

typedef struct chave chave;

typedef struct arvore arvore;

typedef struct dado dado;

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
int insereNo(arvore *arv, int valor, int indice);

/*
Descrição: Aloca uma nova estrutura de chave, e salva ela na lista de chaves da página.
Entrada: Ponteiro para a página onde será inserido, inteiro da chave, inteiro da linha.
Saída: 1 - Sucesso, 0 - Erro.
*/
int insereFolha(pagina *page, int valor, int indice);

/* 
Descrição: Busca de um chave na árvore para coleta do índice para busca posterior no arquivo
Entrada: Ponteiro para a árvore, valor inteiro de busca
Saída: -1 - não há chave com o valor buscado, índice da chave buscada
*/
int buscaArvore(arvore *arv, int valorBusca);

/* 
Entrada: Nome do arquivo, índice de busca
Descrição: Busca no arquivo a partir do índice encontrado na árvore
Saída: 1 - Sucesso, 0 - Falha
*/
int buscaArquivoIndice(char nomeArquivo, int indice);

/* 
Entrada: 
Descrição: busca de informações diretamente no arquivo
Saída: 0 - Falha
*/
int buscaArquivoDireto(char nomeArquivo, int matriculaParametro, dado *dadosColetados);

#endif //INC_13_TRABALHO2_ARVORE_B_H
