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
Descrição: Função que insere um elemento em um pai, sendo que a árvore é de ordem ímpar.
Entrada: Ponteiro para a árvore, ponteiro para a página onde o elemento original foi inserido, valor do elemento que será inserido no pai, e indice.
Saída: 1 - Sucesso, 0 - Erro.
*/
int inserePImpar(arvore *arv, pagina *pai, int valor, int indice);

/*
Descrição: Função que recebe uma página pai, e os indices das páginas filhas que serão divididas. A função olha qual dos filhos é nulo, 
e joga metade dos elementos da outra página para essa nula. Aqui tem 2 casos, se a página original é da esquerda, nós pegamos a metade 
direita e jogamos para ametade esquerda da página direita. Mas se a página original for da direita, nós pegamos a metade esquerda e 
jogamos para a metade esquerda da página esquerda, e pegamos os elementos da metade direita da página original e jogamos na sua metade esquerda.
Entrada: Ponteiro para a árvore, ponteiro para a página pai, indice do irmão esquerdo, indice do irmão direito.
Saída: 1 - Sucesso, 0 - Erro.
*/
int divideIrmao(arvore *arv, pagina *pai, int irmaoEsq, int irmaoDir);

/*
Descriação: Função para rebalancear a árvore, fazendo as divisões das páginas.
Entrada: Ponteiro para a árvore e ponteiro para a página que precisa de correção.
Saída: 1 - Sucesso, 0 - Casos de erro.
*/
int split(arvore *arv, pagina *page);
