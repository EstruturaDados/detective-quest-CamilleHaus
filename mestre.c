#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

/*
====================================================
ESTRUTURA DA SALA (ÁRVORE BINÁRIA DA MANSÃO)
====================================================
Cada sala possui nome, pista e conexões esquerda/direita
*/

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;


/*
====================================================
ESTRUTURA DA BST DE PISTAS
====================================================
Armazena pistas coletadas em ordem alfabética
*/

typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;


/*
====================================================
ESTRUTURA DA TABELA HASH
====================================================
Associa pistas a suspeitos
*/

typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* prox;
} HashNode;

HashNode* tabelaHash[HASH_SIZE];



/*
====================================================
FUNÇÃO HASH
====================================================
Gera índice para a tabela hash baseado na pista
*/

int funcaoHash(const char* pista) {

    int soma = 0;

    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }

    return soma % HASH_SIZE;
}



/*
====================================================
criarSala()

Cria dinamicamente um cômodo da mansão
====================================================
*/

Sala* criarSala(const char* nome, const char* pista) {

    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro de memória\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);

    if (pista != NULL)
        strcpy(novaSala->pista, pista);
    else
        strcpy(novaSala->pista, "");

    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}



/*
====================================================
inserirPista()

Insere pista na BST em ordem alfabética
====================================================
*/

PistaNode* inserirPista(PistaNode* raiz, const char* pista) {

    if (raiz == NULL) {

        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));

        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);

    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}



/*
====================================================
exibirPistas()

Mostra pistas coletadas em ordem alfabética
====================================================
*/

void exibirPistas(PistaNode* raiz) {

    if (raiz != NULL) {

        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}



/*
====================================================
inserirNaHash()

Associa uma pista a um suspeito
====================================================
*/

void inserirNaHash(const char* pista, const char* suspeito) {

    int indice = funcaoHash(pista);

    HashNode* novo = (HashNode*) malloc(sizeof(HashNode));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}



/*
====================================================
encontrarSuspeito()

Retorna o suspeito associado a uma pista
====================================================
*/

char* encontrarSuspeito(const char* pista) {

    int indice = funcaoHash(pista);

    HashNode* atual = tabelaHash[indice];

    while (atual != NULL) {

        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;

        atual = atual->prox;
    }

    return NULL;
}



/*
====================================================
contarPistasSuspeito()

Conta quantas pistas apontam para um suspeito
====================================================
*/

int contarPistasSuspeito(PistaNode* raiz, const char* suspeito) {

    if (raiz == NULL)
        return 0;

    int cont = 0;

    char* s = encontrarSuspeito(raiz->pista);

    if (s != NULL && strcmp(s, suspeito) == 0)
        cont++;

    cont += contarPistasSuspeito(raiz->esquerda, suspeito);
    cont += contarPistasSuspeito(raiz->direita, suspeito);

    return cont;
}



/*
====================================================
verificarSuspeitoFinal()

Fase final do jogo: julgamento
====================================================
*/

void verificarSuspeitoFinal(PistaNode* pistas) {

    char suspeito[50];

    printf("\nDigite o nome do suspeito que você acusa: ");
    scanf(" %[^\n]", suspeito);

    int qtd = contarPistasSuspeito(pistas, suspeito);

    if (qtd >= 2) {

        printf("\nAcusação confirmada!\n");
        printf("Existem %d pistas contra %s.\n", qtd, suspeito);
        printf("Caso resolvido!\n");
    }

    else {

        printf("\nProvas insuficientes!\n");
        printf("Apenas %d pista(s) apontam para %s.\n", qtd, suspeito);
        printf("O culpado escapou...\n");
    }
}



/*
====================================================
explorarSalas()

Controla a exploração da mansão
====================================================
*/

void explorarSalas(Sala* atual, PistaNode** arvorePistas) {

    char escolha;

    while (atual != NULL) {

        printf("\nVocê está em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha um caminho:\n");

        if (atual->esquerda)
            printf("e - esquerda\n");

        if (atual->direita)
            printf("d - direita\n");

        printf("s - sair\n");

        scanf(" %c", &escolha);

        if (escolha == 's')
            return;

        else if (escolha == 'e' && atual->esquerda)
            atual = atual->esquerda;

        else if (escolha == 'd' && atual->direita)
            atual = atual->direita;

        else
            printf("Opção inválida!\n");
    }
}



/*
====================================================
MAIN
====================================================
*/

int main() {

    for (int i = 0; i < HASH_SIZE; i++)
        tabelaHash[i] = NULL;


    inserirNaHash("Pegadas de lama no tapete", "Jardineiro");
    inserirNaHash("Um copo quebrado no chão", "Mordomo");
    inserirNaHash("Cheiro forte de gás", "Cozinheiro");
    inserirNaHash("Livro fora do lugar", "Bibliotecário");
    inserirNaHash("Pegadas levando ao portão", "Jardineiro");
    inserirNaHash("Cofre aberto", "Herdeiro");
    inserirNaHash("Lanterna ainda ligada", "Zelador");


    Sala* hall = criarSala("Hall de Entrada", "Pegadas de lama no tapete");
    Sala* salaEstar = criarSala("Sala de Estar", "Um copo quebrado no chão");
    Sala* cozinha = criarSala("Cozinha", "Cheiro forte de gás");
    Sala* biblioteca = criarSala("Biblioteca", "Livro fora do lugar");
    Sala* jardim = criarSala("Jardim", "Pegadas levando ao portão");
    Sala* quarto = criarSala("Quarto Secreto", "Cofre aberto");
    Sala* porao = criarSala("Porão", "Lanterna ainda ligada");


    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita = porao;


    PistaNode* pistasColetadas = NULL;


    printf("=== DETECTIVE QUEST ===\n");
    printf("Explore a mansão e descubra o culpado!\n");


    explorarSalas(hall, &pistasColetadas);


    printf("\nPistas coletadas:\n");
    exibirPistas(pistasColetadas);


    verificarSuspeitoFinal(pistasColetadas);


    return 0;
}