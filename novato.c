#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/*
    criarSala()
    Cria uma nova sala dinamicamente usando malloc
    e inicializa seus caminhos como NULL.
*/
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/*
    explorarSalas()
    Permite que o jogador navegue pela mansão.
    O jogador pode escolher:
    e - esquerda
    d - direita
    s - sair
*/
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {

        printf("\nVocê está em: %s\n", atual->nome);

        // Se for sala final (nó folha)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas. Fim da exploração!\n");
            return;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL)
            printf("e - ir para a esquerda\n");

        if (atual->direita != NULL)
            printf("d - ir para a direita\n");

        printf("s - sair\n");

        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Exploração encerrada.\n");
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
    main()
    Monta manualmente o mapa da mansão usando árvore binária
    e inicia a exploração a partir do Hall de Entrada.
*/
int main() {

    // Criação das salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* quarto = criarSala("Quarto Secreto");
    Sala* porao = criarSala("Porão");

    // Montagem da árvore da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita = porao;

    printf("=== Detective Quest ===\n");
    printf("Explore a mansão e descubra onde o culpado está!\n");

    // Inicia exploração
    explorarSalas(hall);

    return 0;
}