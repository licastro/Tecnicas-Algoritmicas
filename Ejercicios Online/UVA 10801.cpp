#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

vector<int> Dijkstra(vector<vector<int>>& G, int v0, int a0, int n, int k) {

    vector<vector<int>> dist(100, vector<int>(n, 1e9));
    priority_queue<vector<int>> pq;

    dist[v0][a0] = 0;
    pq.push({0, v0, a0});

    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();

        if (v[0] > dist[v[1]][v[2]]) continue;

        for (int i=0; i< G[v[1]].size(); i+=3) {
            int u = G[v[1]][i], au = G[v[1]][i+1];
            int nueva_dist = dist[v[1]][v[2]] + G[v[1]][i+2];
            if (v[2] != au && v[1]!= 0) nueva_dist += 60;
            if (nueva_dist < dist[u][au]) {
                dist[u][au] = nueva_dist;
                pq.push({nueva_dist, u, au});
            }
        }
    }

    return dist[k];
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> tiempos(n);
        for(int ti = 0; ti < n; ti++) cin >> tiempos[ti];

        int pisoAnterior, pisoSiguiente;
        string line;
        getline(cin, line);

        vector<vector<int>> G(100);
        for(int i = 0; i < n; i++) {
            getline(cin, line);
            istringstream ss(line);
            ss >> pisoAnterior;
            while(ss >> pisoSiguiente) {
                int peso = (pisoSiguiente-pisoAnterior)*tiempos[i];
                G[pisoAnterior].insert(G[pisoAnterior].end(), {pisoSiguiente, i, peso});
                G[pisoSiguiente].insert(G[pisoSiguiente].end(), {pisoAnterior, i, peso});
                pisoAnterior = pisoSiguiente;
            }
        }

        int minimo = 1e9;
        for(int e: Dijkstra(G, 0, 0, n, k)) minimo=min(minimo, e);
        if (minimo < 1e9) cout << minimo << "\n";
        else cout << "IMPOSSIBLE\n";
    }

    return 0;
}


