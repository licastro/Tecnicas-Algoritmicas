#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> padre;
    vector<int> tamano;

    DSU(int n) {
        padre = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n, 1);
    }

    int find(int v) {
        while (padre[v] != v) v = padre[v];
        return v;
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (tamano[u] < tamano[v]) swap(u, v);
        padre[v] = u;
        tamano[u] += tamano[v];
    }
};

pair<double, double> kruskal(vector<vector<int>>& E, int n, double C){

    sort(E.begin(), E.end(), [C](const auto& a, const auto& b) {
        double aC = a[2] - C*a[3];
        double bC = b[2] - C*b[3];
        if (aC == bC) return a[3] < b[3];
        return aC > bC;
    });

    DSU dsu(n);

    double res_d = 0;
    double res_r = 0;
    int aristas = 0;

    for(auto arista : E){
        if(dsu.find(arista[0]) != dsu.find(arista[1])){
            dsu.unite(arista[0],arista[1]);
            res_d += arista[2];
            res_r += arista[3];
            aristas++;
        }
        if(aristas == n-1) break;
    }

    return {res_d , res_r};
}

pair<double, double> maximizar_distancia_repetidoras(vector<vector<int>>& aristas, int n, double high, double low, double epsilon) {

    pair<double, double> acum;
    double n_d;

    while(epsilon <= high - low){

        double mid = (high + low) / 2;
        acum = kruskal(aristas, n, mid);
        n_d = acum.first/acum.second;

        if(n_d == mid) {
            break;
        }

        if (n_d > mid) {
            low = mid;
        } else {
            high = mid;
        }

    }
    return kruskal(aristas, n, n_d);
}

int main() {

    int c;
    scanf("%d", &c);

    while (c--) {
        int n, m;
        scanf("%d %d", &n, &m);
        vector<vector<int>> aristas;
        double cotaS = 0.0;
        double cotaI = 0.0;

        while(m--) {
            int u, v, d, r;
            scanf("%d %d %d %d", &u, &v, &d, &r);
            aristas.push_back({ u, v, d, r });
            cotaS = max(cotaS, 1.0*d/r);
            cotaI += r;
        }

        pair<double, double> resultado;
        cotaI = 1.0/cotaI;
        cotaI = max(cotaI, 1e-6);
        resultado = maximizar_distancia_repetidoras(aristas, n, cotaS, 0, cotaI);
        printf("%lld %lld\n", static_cast<long long>(resultado.first), static_cast<long long>(resultado.second));

    }

    return 0;
}
