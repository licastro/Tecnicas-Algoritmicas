#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

map<string, int> talles = {{"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4}, {"S", 5}, {"XS", 6}};

bool bfs(vector<vector<int>>& red, int s, int t, int n, vector<int>& parent) {

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && red[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v); parent[v] = u; visited[v] = true;
            }
        }
    }
    return false;
}


bool fordFulkerson(int s, int t, vector<vector<int>>& red, int n, int m) {

    vector<int> parent(n, -1);
    int u, v, max_flow = 0;

    while (bfs(red, s, t, n, parent)) {
        int path_flow = 61;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, red[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            red[u][v] -= path_flow;
            red[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow==m;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);

        vector<vector<int>> red(8+M, vector<int>(8+M, 0));
        for (int k=1; k<7; k++) red[0][k] = N / 6;

        string t1, t2;
        int pv, pt1, pt2, pt = 7+M;
        for (int i = 0; i < M; ++i) {
            cin >> t1 >> t2;
            pv = i+7, pt1 = talles[t1], pt2 = talles[t2];
            red[pt1][pv]++; red[pt2][pv]++; red[pv][pt]++;
        }

        if (fordFulkerson(0, pt, red, 8+M, M)) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
