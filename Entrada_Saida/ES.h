typedef struct registro registro;

// Função para criação dos nomes para o registro do arquivo
// Entrada: Seed de criação aleatória
// Saída:   - Nome criado
//          - #-1 para casos de erro
char *criaNome(unsigned long long seed);

// Funcão para criação das matrículas para o registro do arquivo
// Entrada: Seed de criação aleatória
// Saída: Nova matrícula com a seed dada
int criaMatricula(unsigned long long seed);

// Funcão para criação das datas de nascimento para o registro do arquivo
// Entrada: Seed de criação aleatória
// Saída:   - Data de nascimento aleatória
//          - #-1 para casos de erro
char *criaDataNascimento(unsigned long long seed);

// Funcão para criação dos CPFs para o registro do arquivo
// Entrada: Seed de criação aleatória
// Saída: Novo CPF com a seed dada
unsigned long long criaCPF(unsigned long long seed);

// Função para a criação do registro
// Entrada: Seed de criação aleatória
// Saída:   - Estrutura registro preenchida
registro criaRegistro(unsigned long long seed);

// Função para a adição dos registros criados no arquivo
// Entrada: Nome do arquivo, número de registros
// Saída:   0 - Erro ao criar arquivo
//          1 - Sucesso na criação
int criaEntrada(char *nomeArquivo, unsigned long long nroRegistos);

// Função para o preocessamento do arquivo de entrada
// Entrada: Nome do aqruivo
// Sáida:  -1 - Erro na abertura do arquivo
//          0 - Erro na inserção dos dados
int processaEntrada(char* nomeArquivo);