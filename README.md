# Indexador e Buscador de Palavras

Este Exercício Programa (EP) implementa um sistema de indexação e busca de palavras em arquivos de texto utilizando a linguagem C. Desse modo, o objetivo principal é comparar a eficiência de duas estruturas de dados: a **Lista Encadeada** e a **Árvore Binária de Busca**.

Assim, o programa lê um arquivo de texto, verifica o seu conteúdo e constrói um índice que permite que o usuário realize buscas, exibindo as linhas onde as palavras ocorrem e o número de comparações realizadas para encontrar as informações relevantes.

## Estruturas de Dados 

* **Lista:** Insere e busca palavras sequencialmente e, por conseguinte, a complexidade média esperada é $O(n)$.
* **Árvore:** Utiliza uma BST para organizar as palavras e, logo, a complexidade média esperada é $O(\log n)$.

Para além de apenas buscar as palavras, informações importantes como a altura da árvore, o total de palavras únicas indexadas e o número de comparações, tanto na construção do índice, quanto na busca, são também saídas da execução.

## Membros do Grupo

* [**Beatriz dos Santos Bento**](https://github.com/beatriz7227)
* [**Caio Gaspar Paula**](https://github.com/Caio-Gaspar)
* [**Fernanda Yumi Taira**](https://github.com/feyumiii)

## Bibliotecas do C Utilizadas
* `<stdio.h>`: operações de entrada e saída.
* `<stdlib.h>`: gerenciamento de memória.
* `<string.h>`: manipulação de strings.
* `<ctype.h>`: manipulação de caracteres.

## Como Compilar e Executar

### Pré-requisitos
* Compilador GCC ou análogo.
* Um arquivo de texto que passará pela indexação (ex: `texto.txt`).

### Compilação

Para compilar o código, utilize este comando no terminal:

```bash
gcc ep.c -o ep
```
### Execução
O programa aceita argumentos através do terminal para definir o arquivo de entrada e a estrutura de dados a ser utilizada, ou seja, se é uma árvore ou uma lista. Além disso, cabe ressaltar que o arquivo .txt e o ep.c devem estar na mesma pasta para que o programa funcione de forma correta. 

```bash
./ep <Nome do Arquivo .txt> [arvore/lista]
```

## Como Usar
Após a execução e o carregamento do arquivo, o programa exibirá as informações da indexação e abrirá um prompt. Desse modo, os comandos disponíveis são:

1. Buscar uma palavra: digite busca seguido da palavra desejada.
```bash
> busca termo
```
2. Encerrar o programa: digite fim para sair e liberar a memória alocada.
```bash
> fim
```
