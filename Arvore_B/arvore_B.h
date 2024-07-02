/*** -- Estruturas -- ***/

typedef struct pagina pagina;

typedef struct chave chave;

typedef struct arvore arvore;

typedef struct registro registro;

/*** -- Funções -- ***/

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

/*
Descrição: Função que remove a chave especificada da ávore B.
Entrada: Ponteiro para a árvore b, inteiro da chave.
Saída: 1 - Sucesso, 0 - Erro.
*/
int removeChave(arvore *arv, int chave);

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
int buscaArquivoIndice(char nomeArquivo, int indice, registro *dadosColetados);

/* 
Entrada: 
Descrição: busca de informações diretamente no arquivo
Saída: 0 - Falha
*/
int buscaArquivoDireto(char nomeArquivo, int matriculaParametro, registro *dadosColetados);
