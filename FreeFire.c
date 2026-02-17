#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

/* ============================================================
   Struct Item
   Armazena as informações essenciais de cada item da mochila
   ============================================================ */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* ============================================================
   Variáveis globais
   ============================================================ */
Item mochila[MAX_ITENS];
int totalItens = 0;

/* ============================================================
   Função: listarItens
   Exibe todos os itens cadastrados na mochila
   ============================================================ */
void listarItens() {
    printf("\n========= INVENTÁRIO =========\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("Item %d:\n", i + 1);
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("-----------------------------\n");
        }
    }

    printf("==============================\n");
}

/* ============================================================
   Função: inserirItem
   Cadastra um novo item na mochila
   ============================================================ */
void inserirItem() {

    if (totalItens >= MAX_ITENS) {
        printf("\nA mochila está cheia! Limite máximo atingido.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Cadastro de Novo Item ---\n");

    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Tipo do item (arma, municao, cura, ferramenta...): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item cadastrado com sucesso!\n");
}

/* ============================================================
   Função: buscarItem
   Realiza busca sequencial pelo nome do item
   ============================================================ */
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

/* ============================================================
   Função: removerItem
   Remove um item da mochila pelo nome
   ============================================================ */
void removerItem() {
    char nomeRemover[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {

            // Deslocamento dos elementos à esquerda
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

/* ============================================================
   Função principal
   Controla o fluxo do sistema
   ============================================================ */
int main() {

    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO =====\n");
        printf("1 - Cadastrar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
