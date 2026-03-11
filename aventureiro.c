#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
====================================================
ESTRUTURA DA SALA (ÁRVORE BINÁRIA DA MANSÃO)
====================================================
Cada sala possui:
- nome
- pista (opcional)
- ponteiros para esquerda e direita
*/

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;


/*
====================================================
ESTRUTURA DA ÁRVORE DE PISTAS (BST)
====================================================
Cada nó armazena uma pista coletada.
A organização segue ordem alfabética.
*/

typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;



/*
====================================================
criarSala()

Cria dinamicamente uma sala da mansão.
Pode conter ou não uma pista.
====================================================
*/
Sala* criarSala(const char* nome, const char* pista) {

    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro de alocação de memória.\n");
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

Insere uma pista na árvore BST em ordem alfabética.
====================================================
*/
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {

    if (raiz == NULL) {

        PistaNode* nova = (PistaNode*) malloc(sizeof(PistaNode));

        if (nova == NULL) {
            printf("Erro de memória.\n");
            exit(1);
        }

        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;

        return nova;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    }
    else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}



/*
====================================================
exibirPistas()

Percorre a árvore BST em ordem (in-order),
exibindo as pistas em ordem alfabética.
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
explorarSalasComPistas()

Controla a navegação pela mansão.
Sempre que o jogador entra em uma sala com pista,
ela é adicionada automaticamente à árvore BST.
====================================================
*/
void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {

    char escolha;

    while (atual != NULL) {

        printf("\nVocê está em: %s\n", atual->nome);

        // verifica se existe pista
        if (strlen(atual->pista) > 0) {

            printf("Você encontrou uma pista: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha um caminho:\n");

        if (atual->esquerda != NULL)
            printf("e - ir para a esquerda\n");

        if (atual->direita != NULL)
            printf("d - ir para a direita\n");

        printf("s - sair\n");

        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("\nExploração encerrada.\n");
            return;
        }

        else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        }

        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        }

        else {
            printf("Opção inválida!\n");
        }
    }
}



/*
====================================================
FUNÇÃO PRINCIPAL
Cria o mapa da mansão e inicia a exploração.
====================================================
*/

int main() {

    // criação das salas com pistas
    Sala* hall = criarSala("Hall de Entrada", "Pegadas de lama no tapete");

    Sala* salaEstar = criarSala("Sala de Estar", "Um copo quebrado no chão");

    Sala* cozinha = criarSala("Cozinha", "Cheiro forte de gás");

    Sala* biblioteca = criarSala("Biblioteca", "Livro fora do lugar");

    Sala* jardim = criarSala("Jardim", "Pegadas levando ao portão");

    Sala* quarto = criarSala("Quarto Secreto", "Cofre aberto");

    Sala* porao = criarSala("Porão", "Lanterna ainda ligada");


    // montagem da árvore da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita = porao;


    // árvore de pistas coletadas
    PistaNode* pistasColetadas = NULL;


    printf("=== Detective Quest ===\n");
    printf("Explore a mansão e colete pistas!\n");


    explorarSalasComPistas(hall, &pistasColetadas);


    printf("\n=================================\n");
    printf("Pistas coletadas (ordem alfabética):\n");
    printf("=================================\n");

    exibirPistas(pistasColetadas);

    return 0;
}