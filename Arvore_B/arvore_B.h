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
pagina *criaRaiz(arvore *arv, chave valor, pagina *filho);

/*
Descrição: Função para inserção no arquivo de índice.
Entrada: Ponteiro para a raiz da árvore, registro a ser inserido.
Saída: 1 - Sucesso, 0 - Casos de erro.
*/
int insere(arvore *arv, chave valor);
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
int inserePagina(pagina *page, pagina *filho, chave valor, int pos);

/*
Descrição: Função recursiva que encontra em qual filho está o novo registro, até chegar em uma folha. Quando chegar na folha, verifica
    se há espaço, se houver insere nela, se não houver divide o nó e recursivamente vincula com o pai.
Entrada: Ponteiro para a árvore b, estrutura com os valores, ponteiro para os valores (serão alterados na split), ponteiro para a página atual,
    ponteiro de ponteiro para o filho (usada para guardar o novo nó da split na estrutura criada na insere).
Saída: 1 - ou insere, ou da split, ou cria uma nova raiz (são tratados nas funções), 0 - encerra a execução.
*/
int insereChave(arvore *arv, chave registro, chave *pontReg, pagina *page, pagina **filho);

/*
Descrição: Função para corrigir o balanceamento da árvore, realizando a subdivisão da página cheia em duas novas páginas
Entrada: A chave desejada, um endereço para a variável que irá guardar a chave mediana, a página cheia, a página filho,
         um endereço para o novo filho, a posição que será inserida a chave desejada
Saída: 1 - Sucesso, 0 - Casos de erro
*/
int split(chave valor, chave *pontReg, pagina *page, pagina *filho, pagina **newPage, int pos);
