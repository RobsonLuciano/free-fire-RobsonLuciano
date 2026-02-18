#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 100

/* ============================================================
   STRUCTS
   ============================================================ */

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ============================================================
   VARIÁVEIS GLOBAIS
   ============================================================ */

/* Vetor */
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

/* Lista Encadeada */
No* mochilaLista = NULL;

/* Contadores de comparações */
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* ============================================================
   ===================== VETOR ================================
   ============================================================ */

/* Inserção no vetor */
void inserirItemVetor(Item novo) {
    if (totalVetor >= MAX_ITENS) {
        printf("Vetor cheio!\n");
        return;
    }
    mochilaVetor[totalVetor++] = novo;
}

/* Listagem vetor */
void listarVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%s | %s | %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

/* Remoção vetor */
void removerItemVetor(char nome[]) {
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalVetor--;
            printf("Item removido (vetor).\n");
            return;
        }
    }
    printf("Item não encontrado (vetor).\n");
}

/* Busca Sequencial Vetor */
void buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Encontrado no vetor.\n");
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Não encontrado no vetor.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
}

/* Ordenação (Bubble Sort) */
void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome,
                       mochilaVetor[j + 1].nome) > 0) {

                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

/* Busca Binária */
void buscarBinariaVetor(char nome[]) {
    int inicio = 0;
    int fim = totalVetor - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            printf("Encontrado (busca binária).\n");
            printf("Comparações: %d\n", comparacoesBinaria);
            return;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Não encontrado (binária).\n");
    printf("Comparações: %d\n", comparacoesBinaria);
}

/* ============================================================
   ================= LISTA ENCADEADA ==========================
   ============================================================ */

/* Inserção início lista */
void inserirItemLista(Item novo) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
}

/* Listagem lista */
void listarLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = mochilaLista;

    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

/* Remoção lista */
void removerItemLista(char nome[]) {
    No *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                mochilaLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido (lista).\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado (lista).\n");
}

/* Busca Sequencial Lista */
void buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Encontrado na lista.\n");
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("Não encontrado na lista.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
}

/* ============================================================
   ======================== MENU ==============================
   ============================================================ */

Item lerItem() {
    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    return novo;
}

int main() {

    int estrutura;
    int opcao;
    char nomeBusca[30];

    printf("Escolha a estrutura:\n");
    printf("1 - Vetor\n");
    printf("2 - Lista Encadeada\n");
    scanf("%d", &estrutura);

    do {
        printf("\n1-Inserir\n2-Remover\n3-Listar\n4-Busca Sequencial\n");
        if (estrutura == 1)
            printf("5-Ordenar\n6-Busca Binária\n");
        printf("0-Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            Item novo = lerItem();
            if (estrutura == 1)
                inserirItemVetor(novo);
            else
                inserirItemLista(novo);
            break;
        }

        case 2:
            printf("Nome para remover: ");
            scanf(" %[^\n]", nomeBusca);
            if (estrutura == 1)
                removerItemVetor(nomeBusca);
            else
                removerItemLista(nomeBusca);
            break;

        case 3:
            if (estrutura == 1)
                listarVetor();
            else
                listarLista();
            break;

        case 4:
            printf("Nome para buscar: ");
            scanf(" %[^\n]", nomeBusca);
            if (estrutura == 1)
                buscarSequencialVetor(nomeBusca);
            else
                buscarSequencialLista(nomeBusca);
            break;

        case 5:
            if (estrutura == 1)
                ordenarVetor();
            break;

        case 6:
            if (estrutura == 1) {
                printf("Nome para busca binária: ");
                scanf(" %[^\n]", nomeBusca);
                buscarBinariaVetor(nomeBusca);
            }
            break;
        }

    } while (opcao != 0);

    return 0;
}
