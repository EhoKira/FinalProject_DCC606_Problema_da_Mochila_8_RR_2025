// knapsack_dp.c
// 0/1 Knapsack com Programação Dinâmica (2D) + reconstrução
// Compilar: gcc knapsack_dp.c -O2 -o knapsack_dp
// Executar: .\knapsack_dp ou .\knapsack_dp --stdin (Inserir os valores manualmente) 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    int weight;
    int value;
} Item;

typedef struct {
    int *pick;
    int totalWeight;
    int totalValue;
} Solution;

static void print_solution(const Item *items, int n, const Solution *sol, const char *title) {
    printf("\n== %s ==\n", title);
    printf("Valor total: %d\n", sol->totalValue);
    printf("Peso total:  %d\n", sol->totalWeight);
    printf("Itens escolhidos:\n");
    int any = 0;
    for (int i = 0; i < n; i++) {
        if (sol->pick[i]) {
            any = 1;
            if (items[i].name[0] != '\0')
                printf("  - [%d] %s (peso=%d, valor=%d)\n", i, items[i].name, items[i].weight, items[i].value);
            else
                printf("  - [%d] (peso=%d, valor=%d)\n", i, items[i].weight, items[i].value);
        }
    }
    if (!any) printf("  (nenhum item)\n");
}

static Solution solve_knapsack_dp(const Item *items, int n, int C) {
    // dp com (n+1) x (C+1) em bloco único
    int rows = n + 1, cols = C + 1;
    int *dp = (int*)calloc(rows * cols, sizeof(int));
    #define DP(i,w) dp[(i)*cols + (w)]

    for (int i = 1; i <= n; i++) {
        int wi = items[i-1].weight;
        int vi = items[i-1].value;
        for (int w = 0; w <= C; w++) {
            int notake = DP(i-1, w);
            int take = (wi <= w) ? DP(i-1, w - wi) + vi : notake;
            DP(i, w) = (take > notake) ? take : notake;
        }
    }

    Solution sol;
    sol.pick = (int*)calloc(n, sizeof(int));
    sol.totalValue = DP(n, C);

    // Reconstrução
    int w = C;
    for (int i = n; i >= 1; i--) {
        if (DP(i, w) != DP(i-1, w)) {
            sol.pick[i-1] = 1;
            w -= items[i-1].weight;
        }
    }

    int tw = 0;
    for (int i = 0; i < n; i++) if (sol.pick[i]) tw += items[i].weight;
    sol.totalWeight = tw;

    free(dp);
    return sol;
}

static Item* read_instance_stdin(int *outN, int *outC) {
    int n, C;
    if (scanf("%d %d", &n, &C) != 2 || n <= 0 || C < 0) {
        fprintf(stderr, "Formato esperado: n C\\n e depois n linhas 'peso valor'.\\n");
        return NULL;
    }
    Item *items = (Item*)calloc(n, sizeof(Item));
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &items[i].weight, &items[i].value) != 2) {
            fprintf(stderr, "Erro de leitura na linha %d.\\n", i+1);
            free(items);
            return NULL;
        }
        items[i].name[0] = '\0';
    }
    *outN = n; *outC = C;
    return items;
}

static Item* demo_instance(int *outN, int *outC) {
    int n = 5, C = 100;
    Item *demo = (Item*)calloc(n, sizeof(Item));
    strcpy(demo[0].name, "Camera de alta resolucao"); demo[0].weight = 20; demo[0].value = 40;
    strcpy(demo[1].name, "Braco robotico");            demo[1].weight = 50; demo[1].value = 100;
    strcpy(demo[2].name, "Analisador de solo");        demo[2].weight = 30; demo[2].value = 60;
    strcpy(demo[3].name, "Detector de radiacao");      demo[3].weight = 10; demo[3].value = 30;
    strcpy(demo[4].name, "Fonte de energia extra");    demo[4].weight = 40; demo[4].value = 70;
    *outN = n; *outC = C;
    return demo;
}

int main(int argc, char **argv) {
    Item *items = NULL;
    int n = 0, C = 0;
    int use_stdin = (argc >= 2 && strcmp(argv[1], "--stdin") == 0);

    if (use_stdin) {
        items = read_instance_stdin(&n, &C);
        if (!items) return 1;
    } else {
        items = demo_instance(&n, &C);
    }

    Solution sol = solve_knapsack_dp(items, n, C);
    print_solution(items, n, &sol, "Programação Dinâmica (0/1 Knapsack)");

    free(sol.pick);
    free(items);
    return 0;
}