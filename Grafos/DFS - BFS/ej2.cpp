#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool esValida(int a, int b, int t, int& N, int& M, vector<vector<int>>& grilla) {
    bool res = 0 <= a && a < N && 0 <= b && b < M;
    if (res && grilla[a][b] > 0)
        res = t + 1 < grilla[a][b];
    return res;
}

int hospital(int x1, int y1, int x2, int y2, int& N, int& M, vector<vector<int>>& grilla, int tiempoInicio = 0) {
    vector<vector<bool>> visitadas(N, vector<bool>(M, false));
    queue<int> cola;
    int tiempoActual = tiempoInicio;
    int nivel = 1;
    int siguiente_nivel = 0;

    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};

    cola.push(x1);
    cola.push(y1);

    while (!cola.empty()) {
        int x = cola.front();
        cola.pop();
        int y = cola.front();
        cola.pop();

        if (x == x2 && y == y2) {
            return tiempoActual;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (esValida(nx, ny, tiempoActual, N, M, grilla) && !visitadas[nx][ny]) {
                cola.push(nx);
                cola.push(ny);
                visitadas[nx][ny] = true;
                siguiente_nivel++;
            }
        }

        nivel--;
        if (nivel == 0) {
            nivel = siguiente_nivel;
            siguiente_nivel = 0;
            tiempoActual += 1;
        }
    }

    return -1;
}

int main() {
    int c;
    scanf("%d", &c);

    while (c--) {
        int x1, y1, x2, y2, N, M;
        scanf("%d %d", &N, &M);
        vector<vector<int>> grilla(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &grilla[i][j]);
            }
        }
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int resultPaciente = hospital(x1, y1, x2, y2, N, M, grilla);
        if (resultPaciente == -1) printf("IMPOSIBLE\n");
        else {
            int resultVuelta = hospital(x2, y2, x1, y1, N, M, grilla, resultPaciente);
            if (resultVuelta == -1) printf("IMPOSIBLE\n");
            else printf("%d %d\n", resultPaciente, resultVuelta);
        }
    }

    return 0;
}
