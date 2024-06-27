/*** -- Estruturas -- ***/

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
Descrição: Cria uma estrutura da página.
Entrada: Ponteiro para a árvore b.
Saída: Ponteiro para a página; NULL em caso de erro.
*/
pagina *criaPagina(arvore *arv);

/*
Descrição: Insere um elemento na árvore, e chama as funções de correções dependendo do caso.
Entrada: Ponteiro para a árvore b, inteiro da chave, inteiro da linha.
Saída: 1 - Sucesso, 0 - Erro.
*/
int insereNo(arvore *arv, int chave, int indice);

/*
Descrição: Remove um elemento na árvore, e chama as funções auxiliares dependendo do caso.
Entrada: Ponteiro para a árvore b, inteiro da chave.
Saída: 1 - Sucesso, 0 - Erro, -1 - Árvore vazia.
*/
int removeNo(arvore *arv, int chave);

pagina* buscaPagina(pagina* pagina, int chave);
