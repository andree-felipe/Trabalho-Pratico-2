# Desenvolvimento e teste de uma B-Tree.

Este trabalho visa simular um banco de dados na memória RAM do computar com um arquivo de dados, para isso será comparado o tempo para a busca de `n` entradas eleatórias pela B-Tree com a busca diretamente no arquivo de dados.

# Organização
- `Arvore_B`: Contém os códigos da B-Tree.
- `Entrada_Saida`: Contém os códigos para geração de um arquivo de entrada, e para geração de um arquivo de saída com os resultados da busca aleatória.
- `Resultados`: Contém os resultados das buscas aleatórias realizadas.

- `entrada.txt`: Arquivo de dados utilizado.
- `main.c`: Código principal do programa.

# Resultados
## Ambiente de desenvolvimento:
- Processador: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz   3.00 GHz
- Sistema Operacional: Windows 11 Home Single Language
- Ambiente de Desenvolvimento: VSCode
- Versão do GCC: 11.4.0
- Memória RAM: 12.0 GB

## Resultado para as buscas por índice:
| Chaves | Métodos | Tempo (ms) |
| ------ | ------- | ---------- |
|  | Mínimo | 0.004 |
| 30 | Média | 0.0188 |
|  | Máxima | 0.258 |
|  | Mínimo | 0.004 |
| 100 | Média | 0.0294 |
|  | Máxima | 0.5190 |
|  | Mínimo | 0.003 |
| 1000 | Média | 0.0350 |
|  | Máxima | 2.897 |
|  | Mínimo | 0.002 |
| 10000 | Média | 0.0249 |
|  | Máxima | 3.5160 |
