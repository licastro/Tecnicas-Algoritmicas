#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> aristasDe;
vector<vector<int>> indiceEnLista;
vector<pair<int, int>> aristas;
int n, m, NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
bool hayPuente = false;

void dfs(int v, vector<vector<int>> &tree_edges, vector<int> &back_edges_con_extremo_inferior_en, vector<int> &back_edges_con_extremo_superior_en, vector<int> &estado, int p = -1) {
    estado[v] = EMPECE_A_VER;
    for (pair<int, int> par : aristasDe[v]) {
        if (par.first == -1) {
            continue;
        }
        int u = par.first;
        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            dfs(u, tree_edges, back_edges_con_extremo_inferior_en, back_edges_con_extremo_superior_en, estado, v);
        } else if (u != p) {
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_inferior_en[v]++;
            } else { // estado[u] == TERMINE_DE_VER
                back_edges_con_extremo_superior_en[v]++;
            }
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int buscarPuente(int v, vector<int> &memo, vector<vector<int>> &tree_edges, vector<int> &back_edges_con_extremo_inferior_en, vector<int> &back_edges_con_extremo_superior_en, int p = -1) {
    if (memo[v] != -1) return memo[v];
    int sum = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            sum += buscarPuente(hijo, memo, tree_edges, back_edges_con_extremo_inferior_en, back_edges_con_extremo_superior_en, v);
        }
    }
    sum -= back_edges_con_extremo_superior_en[v];
    sum += back_edges_con_extremo_inferior_en[v];
    memo[v] = sum;
    if (v != 0) {
        hayPuente |= sum == 0;
    }
    return sum;
}

void calcularAristasImportantes() {
    int res = 0;
    vector<vector<int>> aristasImportantes(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u = aristas[i].first;
        int v = aristas[i].second;
        int indiceU = indiceEnLista[u][v]; // devuelve el índice de u en aristasDe[v]
        int indiceV = aristasDe[v][indiceU].second;
        aristasDe[u][indiceV] = {-1, -1};
        aristasDe[v][indiceU] = {-1, -1};
        vector<vector<int>> tree_edges(n, vector<int>());
        vector<int> back_edges_con_extremo_inferior_en(n, 0);
        vector<int> back_edges_con_extremo_superior_en(n, 0);
        vector<int> memo(n, -1);
        vector<int> estado(n, 0);
        dfs(0, tree_edges, back_edges_con_extremo_inferior_en, back_edges_con_extremo_superior_en, estado);
        buscarPuente(0, memo, tree_edges, back_edges_con_extremo_inferior_en, back_edges_con_extremo_superior_en);
        if (hayPuente) {
            aristasImportantes[min(u, v)].push_back(max(u, v));
            res++;
        }
        hayPuente = false;
        aristasDe[u][indiceV] = {v, indiceU};
        aristasDe[v][indiceU] = {u, indiceV};
    }
    printf("%d\n", res);
    for (int i = 0; i < n; i++) {
        sort(aristasImportantes[i].begin(), aristasImportantes[i].end());
    }
    for (int i = 0; i < n; i++) {
        int cantAristas = aristasImportantes[i].size();
        for (int j = 0; j < cantAristas; j++) {
            int aristaActual = aristasImportantes[i][j];
            printf("%d %d\n", i, aristaActual);
        }
    }
}

int main() {
    // La primera línea indica la cantidad de tests
    int cant_tests;
    scanf("%d", &cant_tests);
    int u, v;
    // Ingreso los casos de test:
    while (cant_tests--) {
        // La segunda línea del test contiene la cantidad de vértices y aristas respectivamente
        scanf("%d %d", &n, &m);
        indiceEnLista.resize(n, vector<int>(n, -1));
        aristasDe.resize(n, vector<pair<int, int>>());
        // Las siguientes m líneas son las aristas
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            aristas.push_back({u, v});
            int indiceV = aristasDe[u].size(); // índiceV = índice de v en aristasDe[u]
            int indiceU = aristasDe[v].size(); // índiceU = índice de u en aristasDe[v]
            indiceEnLista[u][v] = indiceU;
            aristasDe[u].push_back({v, indiceU});
            aristasDe[v].push_back({u, indiceV});
        }
        calcularAristasImportantes();
        aristasDe.clear();
        indiceEnLista.clear();
        aristas.clear();
    }
    return 0;
}
