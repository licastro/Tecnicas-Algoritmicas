#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int X, Y, P;
map<char, int> valores = {{'*', 1}, {'.', 1}, {'@', 1e9}, {'#', 1e9}, {'~', 0}};

int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1); parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});
    while (!q.empty()) {
        int cur = q.front().first, flow = q.front().second;
        q.pop();
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t, int N, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int new_flow, flow = 0;
    vector<int> parent(N);
    while (new_flow = bfs(s, t, parent, capacity, adj)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            if (capacity[prev][prev] == -1) { for (int i = 0; i < N; i++) capacity[prev][i] = 0; }
            capacity[cur][prev] += new_flow; cur = prev;
        }
    }
    return flow;
}

int main() {

    while (scanf("%d %d %d", &X, &Y, &P) == 3) {
        char c;
        int n = 2*(X*Y)+2;
        vector<vector<int>> capacity(n, vector<int>(n)), adj(n);
        
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                scanf(" %c", &c);
                int v = valores[c], indiceOut = 2*(i*Y+j)+1, indiceIn = indiceOut+1;
                
                capacity[indiceIn][indiceOut] = v; adj[indiceOut].push_back(indiceIn); adj[indiceIn].push_back(indiceOut);
                if (c == '*') { capacity[0][indiceIn]++; adj[0].push_back(indiceIn); adj[indiceIn].push_back(0); }
                else if (c == '#') { capacity[indiceOut][n - 1] = P; adj[indiceOut].push_back(n - 1); adj[n - 1].push_back(indiceOut); }
                
                if (j != 0) { capacity[indiceOut][indiceIn - 2] = v; adj[indiceOut].push_back(indiceIn - 2); adj[indiceIn - 2].push_back(indiceOut); }
                if (j != Y-1) { capacity[indiceOut][indiceIn + 2] = v; adj[indiceOut].push_back(indiceIn + 2); adj[indiceIn + 2].push_back(indiceOut); }
                if (i != 0) { capacity[indiceOut][indiceIn - 2 * Y] = v; adj[indiceOut].push_back(indiceIn - 2 * Y); adj[indiceIn - 2 * Y].push_back(indiceOut); }
                if (i != X-1) { capacity[indiceOut][indiceIn + 2 * Y] = v; adj[indiceOut].push_back(indiceIn + 2 * Y); adj[indiceIn + 2 * Y].push_back(indiceOut); }
            }
        }
        printf("%d\n", maxflow(0, n-1, n, capacity, adj));
    }
    return 0;
}
