# FinalProject_DCC606_Problema_da_Mochila_8_RR_2025

Implementações do Problema da Mochila 0/1 em **C**:
- **Backtracking** (DFS com poda por capacidade)
- **Programação Dinâmica 2D** (`dp[i][c]` + reconstrução da solução)

Aplicação prática: **seleção de payload** para um rover em **missão espacial** (capacidade de massa limitada).

---

## 📁 Estrutura

├─ Algoritmos/

│ ├─ knapsack_backtracking.c

│ └─ knapsack_dp.c

├─ Documentação/

│ ├─ Relatório_problema_mochila.pdf

| └─ Slide do Problema da Mochila 10.pdf

├─ LICENSE

└─ README.md

---

### 🛰️ Instância (Missão Espacial)
- Capacidade: C = 100 kg

- Itens (massa, valor):

  - Câmera de alta resolução — (20, 40)

  - Braço robótico — (50, 100)

  - Analisador de solo — (30, 60)

  - Detector de radiação — (10, 30)

  - Fonte de energia extra — (40, 70)

Resultado esperado: valor ótimo 200, massa total 100 kg
(Existem múltiplas combinações ótimas; qualquer uma é válida.)

---

Windows (MinGW):
```bash
mkdir Algoritmos
gcc knapsack_backtracking.c -o2 -o knapsack_bt
./knapsack_bt ou ./knapsack_bt --stdin

gcc knapsack_dp.c -O2 -o knapsack_dp
.\knapsack_dp ou .\knapsack_dp --stdin
```



### 🔗 Referências
FUKASAWA, R.; NAOUM-SAWAYA, J.; OLIVEIRA, D. The Price-Elastic Knapsack Problem. Omega, v. 124, 2024, art. 103003. DOI: 10.1016/j.omega.2023.103003.
