#include <iostream>
#include <vector>

using namespace std;

struct Edge { int a, b, cost; };

bool bellmanFord(int n, vector<Edge>& edges){
    vector<int> d(n, 0);
    d[0] = 0;

    for (int i = 0; i < n-1; ++i) for (Edge e: edges) if (d[e.b] > d[e.a] + e.cost) d[e.b] = d[e.a] + e.cost;
    for (Edge e : edges) if (d[e.a] + e.cost < d[e.b]) return false;

    return true;
}

int main() {

    while (true) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0) break;

        vector<Edge> edges;
        while(m--) {
            int si, ni, ki;
            char oi[3];
            scanf("%d %d %2s %d", &si, &ni, oi, &ki);
            if (oi[0] == 'g') edges.push_back({si+ni, si-1, -ki-1});
            else edges.push_back({si-1, si+ni, ki-1});
        }

        if (bellmanFord(n+1, edges)) printf("lamentable kingdom\n");
        else printf("successful conspiracy\n");
    }

    return 0;
}



