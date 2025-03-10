#include <iostream>
#include <vector>

using namespace std;

int calcular_movimientos(int clave1, int clave2) {
    int total_movimientos = 0;
    for (int i = 0; i < 4; ++i) {
        int distancia = abs(clave1 % 10 - clave2 % 10);
        total_movimientos += min(distancia, 10 - distancia);
        clave1 /= 10;
        clave2 /= 10;
    }
    return total_movimientos;
}

int costo_agm(vector<vector<int>>& g){

    int n = g.size(), res = 0;
    vector<bool> es_rojo(g.size());
    es_rojo[0] = true;
    vector<int> rojo_mas_cercano(n,0);

    for(int it = 0; it < n-1; it++){
        int w = 0;
        while(es_rojo[w]) w++;
        for(int u = w; u < n; u++){
            if(!es_rojo[u] and g[u][rojo_mas_cercano[u]] < g[w][rojo_mas_cercano[w]]) {
                w = u;
            }
        }
        res += g[w][rojo_mas_cercano[w]];
        es_rojo[w] = true;
        for(int v = 0; v < n; v++){
            if(!es_rojo[v] and g[w][v] < g[v][rojo_mas_cercano[v]])
                rojo_mas_cercano[v] = w;
        }

    }

    return res;
}

int main() {

    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        scanf("%d", &n);

        vector<int> claves(n);
        int inicio = 40;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &claves[i]);
            inicio = min(inicio, calcular_movimientos(0000, claves[i]));
        }

        vector<vector<int>> g(n,vector<int>(n,40));
        for(int u = 0; u < n; u++){
            for(int v = u+1; v < n; v++) g[u][v] = g[v][u] = calcular_movimientos(claves[u], claves[v]);
        }

        printf("%d\n", costo_agm(g) + inicio);

    }

    return 0;
}
