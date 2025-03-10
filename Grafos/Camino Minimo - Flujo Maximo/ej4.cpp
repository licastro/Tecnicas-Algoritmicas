#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

/*

tenemos una cota para la cant de herramientas de cada persona y es la suma de todas las aristas / cant de personas
Podemos ir probando empezando por ese valor e ir decrementando en caso de no encontrar una solucion con esa cantidad de herramientas
El modelo consiste en, dada una cant de herramientas k, cambiamos las capacidades de las aristas x la cantidad de personas q podrian pasar x esa arista llevando k herramientas. Por ejemplo si una arista tiene capacidad 7 y estamos probando con k = 3, podrian pasar 2 personas por esa arista, entonces su capacidad pasa a ser 2. Encontramos una solucion si al buscar el flujo maximo sobre ese modelo nos termina quedando exactamente la cantidad de personas sobre las q tenemos q dividir el trabajo

*/

int n, INF = 1e9;

int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                //cout << "flow = " << new_flow << endl;
                if (next == t){
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(n+1);
    int new_flow;
    while (new_flow = bfs(s, t, parent, capacity, adj)) {
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

int main(){

    //La primera linea indica la cantidad de tests
    int cant_tests;
    scanf("%d", &cant_tests);
    int m, personas_ej;
    //Ingreso los casos de test:
    while(cant_tests--){
        //La segunda linea del test contiene la cantidad de vertices, aristas y personas
        scanf("%d %d %d", &n, &m, &personas_ej);
        vector<vector<int>> adj(n+1), capacity(n+1, vector<int>(n+1, 0)), newCapacity(n+1, vector<int>(n+1, 0));
        vector<tuple<int, int, int>> aristas(m);
        int u, v, c;
        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &u, &v, &c);
            capacity[u][v] = c;
            newCapacity[u][v] = c;
            aristas[i] = make_tuple(u, v, c);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        //cout << "maxflow: " << flujoMax << endl;
        int res = 0;
        int maxPersonas = maxflow(1, n, newCapacity, adj);
        /* En vez de arrancar probando con cantArtefactos = flujoMax/personas_ej e ir decrementando de a 1 podemos hacer busqueda binaria capaz es mas eficiente. Arrancamos con el rango de 1 a flujoMax/personas_ej. Si en el valor a la mitad de ese rango entran mas personas que personas_ej sabemos q tenemos q ir en el rango desde la mitad hasta flujoMax/personas_ej. Sino, entre 1 y la mitad */
        if(maxPersonas >= personas_ej){
            int desde = 0, hasta = maxPersonas+1, cantArtefactos = 1, ultimaBuena = 0, maxPersonasTotal = -1;
            while(desde+1 < hasta){
                //cout << "Con cantArtefactos = " << cantArtefactos << " entran " << maxPersonas << " personas" << endl;
                if(maxPersonas >= personas_ej){
                    desde = cantArtefactos;
                } else {
                    hasta = cantArtefactos;
                }
                cantArtefactos = (desde+hasta)/2;
                /*for(int i = 0; i < aristas.size(); i++){
                    tuple<int, int, int> actual = aristas[i];
                    u = get<0>(actual);
                    v = get<1>(actual);
                    c = get<2>(actual);
                    newCapacity[u][v] = c/cantArtefactos;
                    newCapacity[v][u] = 0;
                    //cout << "La nueva capacidad de la arista " << u << " " << v << " es: " << c/cantArtefactos << endl;
                }*/
                for (int i = 0; i <= n; i++) {
                    for (int j = 0; j <= n; j++) {
                        newCapacity[i][j] = capacity[i][j]/cantArtefactos;
                    }
                }
                maxPersonas = maxflow(1, n, newCapacity, adj);
            }
            res = personas_ej * cantArtefactos;
        }
        printf("%d\n", res); 
    }
    return 0;
}
