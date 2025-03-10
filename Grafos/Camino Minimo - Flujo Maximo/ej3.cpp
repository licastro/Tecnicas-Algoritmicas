#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void crearGrafoBipartito(vector<vector<int>>& gb, int& sf, int& sc, int N) {
    int casillero_actual;
    vector<int> fila_actual;
    vector<int> fila_anterior;
    vector<int> nueva_subcolumna(N);
    for (int l = 0; l < N; l++) {
        nueva_subcolumna[l] = l;
    }

    for (int i = 0; i < N; ++i) {
        gb.push_back({});
        for (int j = 0; j < N; ++j) {
            scanf("%d", &casillero_actual);
            fila_actual.push_back(casillero_actual);
            if (casillero_actual == 1) {
                if (i!=0 && i !=N-1 && fila_anterior[j]!=1) {
                    sc++;
                    nueva_subcolumna[j] = sc-1;
                }
                if (j!=0 && j !=N-1 && fila_actual[j-1]!=1) {
                    gb.push_back({});
                    sf++;
                }
            }
            else {
                gb[sf].push_back(nueva_subcolumna[j]);
            }
        }
        fila_anterior = fila_actual;
        fila_actual.clear();
        sf++;
    }

}

int completarAdjCapacity (vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& gb, int sf, int sc) {
    adj = vector<vector<int>>(sf + sc + 2);
    capacity = vector<vector<int>>(sf + sc + 2, vector<int>(sf + sc + 2, 0));

    int s = 0;
    int t = sf + sc + 1;
    
    for (int i = 1; i <= sf; i++) {
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = 1;
        for (int nodo : gb[i-1]) {
            adj[i].push_back(nodo + sf+1);
            adj[nodo+sf+1].push_back(i);
            capacity[i][nodo + sf + 1] = 1;
        }
    }

    for (int j = 1; j <= sc; j++) {
        adj[j + sf].push_back(t);
        adj[t].push_back(j+sf);
        capacity[j + sf][t] = 1;
    }

    return t;
}

int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj, int n) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    int c;
    scanf("%d", &c);

    while (c--) {
        int N;
        scanf("%d", &N);

        vector<vector<int>> g_bipartito;
        int subfila = 0;
        int subcolumna = N;

        crearGrafoBipartito(g_bipartito, subfila, subcolumna, N);

        vector<vector<int>> capacity;
        vector<vector<int>> adj;
        int t = completarAdjCapacity(adj, capacity, g_bipartito, subfila, subcolumna);

        int resultado = maxflow(0, t, capacity, adj, t + 1);
        printf("%d\n", resultado);
    }
    return 0;
}
