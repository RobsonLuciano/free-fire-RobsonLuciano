#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

/* ============================================================
   STRUCT Componente
   Representa cada peça necessária para a torre de fuga
   ============================================================ */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

/* Contadores globais */
long comparacoes = 0;

/* ============================================================
   Função para limpar \n do fgets
   ============================================================ */
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* ============================================================
   Exibir componentes
   ============================================================ */
void mostrarComponentes(Componente v[], int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-15s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* ============================================================
   Bubble Sort por NOME
   ============================================================ */
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

/* ============================================================
   Insertion Sort por TIPO
   ============================================================ */
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else break;
        }
        v[j + 1] = chave;
    }
}

/* ============================================================
   Selection Sort por PRIORIDADE
   ============================================================ */
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

/* ============================================================
   Busca Binária por Nome (requer ordenação por nome)
   ============================================================ */
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;
    long comparacoesBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;

        int cmp = strcmp(v[meio].nome, nome);

        if (cmp == 0) {
            printf("\nComponente-chave encontrado!\n");
            printf("Comparações na busca: %ld\n", comparacoesBusca);
            return meio;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nComponente-chave NÃO encontrado.\n");
    printf("Comparações na busca: %ld\n", comparacoesBusca);
    return -1;
}

/* ============================================================
   Medir tempo de execução
   ============================================================ */
void medirTempo(void (*algoritmo)(Componente[], int),
                Componente v[], int n) {

    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Comparações: %ld\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {

    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    char nomeBusca[30];

    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &total);
    getchar(); // limpar buffer

    if (total > MAX_COMPONENTES)
        total = MAX_COMPONENTES;

    /* Cadastro */
    for (int i = 0; i < total; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        removerQuebraLinha(componentes[i].nome);

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        removerQuebraLinha(componentes[i].tipo);

        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n===== MENU FINAL =====\n");
        printf("1 - Ordenar por Nome (Bubble Sort)\n");
        printf("2 - Ordenar por Tipo (Insertion Sort)\n");
        printf("3 - Ordenar por Prioridade (Selection Sort)\n");
        printf("4 - Buscar Componente-chave (binária por nome)\n");
        printf("5 - Mostrar Componentes\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                medirTempo(bubbleSortNome, componentes, total);
                mostrarComponentes(componentes, total);
                break;

            case 2:
                medirTempo(insertionSortTipo, componentes, total);
                mostrarComponentes(componentes, total);
                break;

            case 3:
                medirTempo(selectionSortPrioridade, componentes, total);
                mostrarComponentes(componentes, total);
                break;

            case 4:
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                removerQuebraLinha(nomeBusca);
                buscaBinariaPorNome(componentes, total, nomeBusca);
                break;

            case 5:
                mostrarComponentes(componentes, total);
                break;

        }

    } while (opcao != 0);

    return 0;
}
