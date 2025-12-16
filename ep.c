#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 10000 
#define TAMANHO_TEXTO 1000

typedef struct _no_palavra_ {
    char *valor;
    struct _no_palavra_ *proximo;
} NoPalavra;

typedef struct _no_linha_ {
    NoPalavra *lista_palavras;
} NoLinha;

typedef struct _ref_linha_ {
    int numero_linha;
    struct _ref_linha_ *proximo;
} RefLinha;

typedef struct _dados_palavra_ {
    char *palavra;
    int contagem;
    RefLinha *casos; 
    struct _dados_palavra_ *proximo; // só usa na lista ligada
} DadosPalavra;

typedef struct _no_arvore_ {
    DadosPalavra *conteudo;
    struct _no_arvore_ *esq;
    struct _no_arvore_ *dir;
} NoArvore;


// para colocar qual linha corresponde ao caso
void LinhaCaso(RefLinha **inicio, int linha){
    if (*inicio == NULL){
        *inicio = (RefLinha *)malloc(sizeof(RefLinha));
        if (!*inicio){
            exit(1);
        }
        (*inicio)->numero_linha = linha;
        (*inicio)->proximo = NULL;
    }else{
        RefLinha *atual = *inicio;
        while (atual->proximo != NULL){
            atual = atual->proximo;            
        }
        if (atual->numero_linha != linha){
            RefLinha *novo = (RefLinha *)malloc(sizeof(RefLinha));
            novo->numero_linha = linha;
            novo->proximo = NULL;
            atual->proximo = novo;
        }
    }
}

void LiberaCasos(RefLinha *inicio){
    while (inicio){
        RefLinha *temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}

// funções de lista 

void InsereLista(DadosPalavra **inicio, char *palavra, int linha, int *comparacoes){
    DadosPalavra *atual = *inicio;
    DadosPalavra *anterior = NULL;

    while (atual != NULL){
        (*comparacoes)++;
        if (strcmp(atual->palavra, palavra) == 0){
            atual->contagem++;
            LinhaCaso(&(atual->casos), linha);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    // se a palavra não está, insere novo nó
    DadosPalavra *novo = (DadosPalavra *)malloc(sizeof(DadosPalavra));
    if (!novo){
        exit(1);
    }
    novo->palavra = strdup(palavra);
    if (!novo->palavra){
        exit(1);
    }

    novo->contagem = 1;
    novo->casos = NULL;
    novo->proximo = NULL;
    LinhaCaso(&(novo->casos), linha);

    if (anterior == NULL) *inicio = novo;
    else anterior->proximo = novo;
}

DadosPalavra *BuscaLista(DadosPalavra *inicio, const char *palavra, int *comparacoes){
    DadosPalavra *atual = inicio;
    while (atual != NULL){
        (*comparacoes)++;
        if (strcmp(atual->palavra, palavra) == 0){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int ContaLista(DadosPalavra *inicio){
    int total = 0;
    while (inicio){
        total++;
        inicio = inicio->proximo;
    }
    return total;
}

void LiberaLista(DadosPalavra *inicio){
    while (inicio){
        DadosPalavra *temp = inicio;
        inicio = inicio->proximo;
        free(temp->palavra);
        LiberaCasos(temp->casos);
        free(temp);
    }
}

// funções de árvore

NoArvore* CriaNo(char *palavra, int linha) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (!no){
        exit(1);
    }
    no->conteudo = (DadosPalavra *)malloc(sizeof(DadosPalavra));
    if (!no->conteudo){
        exit(1);
    }
    
    no->conteudo->palavra = strdup(palavra); 
    if (!no->conteudo->palavra){
        exit(1);
    }

    no->conteudo->contagem = 1;
    no->conteudo->casos = NULL;
    no->conteudo->proximo = NULL; // não usa na árvore
    LinhaCaso(&(no->conteudo->casos), linha);

    no->esq = NULL;
    no->dir = NULL;
    return no;
}

NoArvore* InsereArvore(NoArvore *raiz, char *palavra, int linha, int *comparacoes){
    if (raiz == NULL){
        return CriaNo(palavra, linha);
    }
    (*comparacoes)++;
    int comparacao = strcmp(palavra, raiz->conteudo->palavra);

    if (comparacao == 0){
        raiz->conteudo->contagem++;
        LinhaCaso(&(raiz->conteudo->casos), linha);
    }else if (comparacao < 0){
        raiz->esq = InsereArvore(raiz->esq, palavra, linha, comparacoes);
    }else{
        raiz->dir = InsereArvore(raiz->dir, palavra, linha, comparacoes);
    }
    return raiz;
}

DadosPalavra* BuscaArvore(NoArvore *raiz, const char *palavra, int *comparacoes){
    if (raiz == NULL){
        return NULL;
    }

    (*comparacoes)++;
    int comparacao = strcmp(palavra, raiz->conteudo->palavra);

    if (comparacao == 0){
        return raiz->conteudo;
    } 
    if (comparacao < 0){
        return BuscaArvore(raiz->esq, palavra, comparacoes);
    } 
    return BuscaArvore(raiz->dir, palavra, comparacoes);
}

int Altura(NoArvore *raiz){
    if (raiz == NULL){
        return 0;
    }

    int altura_esquerda = Altura(raiz->esq);
    int altura_direita = Altura(raiz->dir);

    if (altura_esquerda > altura_direita){
        return 1 + altura_esquerda;
    }else{
        return 1 + altura_direita;
    }
}

void QuantidadeArvore(NoArvore *raiz, int *total) {
    if (raiz){
        (*total)++;
        QuantidadeArvore(raiz->esq, total);
        QuantidadeArvore(raiz->dir, total);
    }
}

void LiberaArvore(NoArvore *raiz){
    if (raiz){
        LiberaArvore(raiz->esq);
        LiberaArvore(raiz->dir);
        free(raiz->conteudo->palavra);
        LiberaCasos(raiz->conteudo->casos);
        free(raiz->conteudo);
        free(raiz);
    }
}


void PrintaOriginal(NoLinha *linha){
    NoPalavra *p = linha->lista_palavras;
    while (p){
        printf("%s", p->valor);
        if (p->proximo != NULL){
            printf(" ");
        }
        p = p->proximo;
    }
}

void PrintaCasos(DadosPalavra *resultado, NoLinha **indice, int total_linhas){
    if (!resultado) return;
    
    RefLinha *caso = resultado->casos;
    while (caso){
        if (caso->numero_linha > 0 && caso->numero_linha <= total_linhas){
            printf("%05d: ", caso->numero_linha);
            if (indice[caso->numero_linha]){
                PrintaOriginal(indice[caso->numero_linha]);
            }
            printf("\n");
        }
        caso = caso->proximo;
    }
}

void LiberaTexto(NoLinha **indice, int total_linhas){
    for (int i = 1; i <= total_linhas; i++){
        if (indice[i]){
            NoPalavra *p = indice[i]->lista_palavras;
            while (p){
                NoPalavra *temp = p;
                p = p->proximo;
                free(temp->valor);
                free(temp);
            }
            free(indice[i]);
        }
    }
}


int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    int arvore = 0;
    if (argc >= 3 && strcmp(argv[2], "arvore") == 0){
        arvore = 1;
    }

    int capacidade_atual = TAMANHO;
    NoLinha **indice_texto = (NoLinha **)malloc(capacidade_atual * sizeof(NoLinha *));
    for (int i = 0; i < capacidade_atual; i++){
        indice_texto[i] = NULL;
    }

    DadosPalavra *dicionario_lista = NULL;
    NoArvore *raiz_arvore = NULL;
    
    char linha_lida[TAMANHO]; 
    int contador_linha = 0;
    int comparacoes_construcao = 0;

    while (fgets(linha_lida, TAMANHO, in)){
        contador_linha++;
        if (contador_linha >= capacidade_atual){
            int nova_capacidade = capacidade_atual * 2;
            NoLinha **temp = (NoLinha **)realloc(indice_texto, nova_capacidade * sizeof(NoLinha *));
            indice_texto = temp;
            
            for (int i = capacidade_atual; i < nova_capacidade; i++){
                indice_texto[i] = NULL;
            }
            capacidade_atual = nova_capacidade;
        }

        // tira quebra de linha
        for (int i = 0; linha_lida[i] != '\0'; i++){
            if (linha_lida[i] == '\n'){
                linha_lida[i] = '\0';
                break;
            }
        }

        // gurda o texto original
        NoLinha *nova_linha = (NoLinha *)malloc(sizeof(NoLinha));
        nova_linha->lista_palavras = NULL;
        
        char *copia_texto = strdup(linha_lida);
        char *token = strtok(copia_texto, " ");
        NoPalavra *ultima_palavra = NULL;

        while (token){
            NoPalavra *p = (NoPalavra *)malloc(sizeof(NoPalavra));
            p->valor = strdup(token);
            p->proximo = NULL;

            if (!nova_linha->lista_palavras) nova_linha->lista_palavras = p;
            else ultima_palavra->proximo = p;
            
            ultima_palavra = p;
            token = strtok(NULL, " ");
        }
        free(copia_texto);
        
        indice_texto[contador_linha] = nova_linha;
        char *copia_indice = strdup(linha_lida); 

        token = strtok(copia_indice, " \t\r.,;?!:-()\"/");
        
        while (token){
            if (strlen(token) > 0){
                for(int i = 0; token[i]; i++){
                    token[i] = tolower((unsigned char)token[i]);
                }
                if (arvore){
                    raiz_arvore = InsereArvore(raiz_arvore, token, contador_linha, &comparacoes_construcao);
                }else{
                    InsereLista(&dicionario_lista, token, contador_linha, &comparacoes_construcao);
                } 
            }
            token = strtok(NULL, " \t\r.,;?!:-()\"/");
        }
        free(copia_indice);
    }
    fclose(in);

    // no terminal:
    printf("Arquivo: '%s'\n", argv[1]);
    if (arvore){
        printf("Tipo de indice: 'arvore'\n");
    }else{
        printf("Tipo de indice: 'lista'\n");
    }    
    printf("Numero de linhas no arquivo: %d\n", contador_linha);

    int total_unicas = 0;
    if (arvore){
        QuantidadeArvore(raiz_arvore, &total_unicas);
    }else{
        total_unicas = ContaLista(dicionario_lista);
    }
    
    printf("Total de palavras unicas indexadas: %d\n", total_unicas);
    if (arvore){
        printf("Altura da arvore: %d\n", Altura(raiz_arvore));
    } 
    printf("Numero de comparacoes realizadas para a construcao do indice: %d\n", comparacoes_construcao);

    // função  de busca
    char linha_comando[TAMANHO_TEXTO];
    char comando[50], termo[TAMANHO_TEXTO];

    printf("\n> ");
    while (fgets(linha_comando, sizeof(linha_comando), stdin)){
        int lidos = sscanf(linha_comando, "%s %s", comando, termo);
        if (lidos > 0 && strcmp(comando, "fim") == 0)
        break;

        if (lidos == 2 && strcmp(comando, "busca") == 0){
            int comp_busca = 0;
            DadosPalavra *resultado = NULL;
            
            for(int i = 0; termo[i]; i++){
                if (termo[i] >= 'A' && termo[i] <= 'Z'){
                    termo[i] = termo[i] + 32; 
                }
            }

            if (arvore){
                resultado = BuscaArvore(raiz_arvore, termo, &comp_busca);
            }else{
                resultado = BuscaLista(dicionario_lista, termo, &comp_busca);
            }

            printf("\n"); 
            if (resultado){
                printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", resultado->contagem, termo);
                PrintaCasos(resultado, indice_texto, contador_linha);
            }else{
                printf("Palavra '%s' nao encontrada.\n", termo);
            }
            printf("Numero de comparacoes: %d\n", comp_busca);
        }else{
            printf("Opcao invalida!\n");
        }
        printf("\n> ");
    }

    if (arvore){
        LiberaArvore(raiz_arvore);
    }else{
        LiberaLista(dicionario_lista);
    }
    
    LiberaTexto(indice_texto, contador_linha);
    free(indice_texto);

    return 0;
}