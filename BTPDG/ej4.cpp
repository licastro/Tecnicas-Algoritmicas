#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

/*

 Partimos de la hipótesis que la mejor disposición va a ser aquella en la que las posiciones de las proveedurías
 coincidan con los puestos de choripanes.

 La proveeduría más cercana para cada puesto se decide entre la que tiene más cerca a la derecha, y más cerca a la izquierda:
 C({p_izq, p_der}) calcula la suma de la mínima distancia para puesto p_j en [p_izq: p_der]. Están los dos casos especiales, si no tiene
 puesto a la izquierda, C({p_der}), y si no tiene puesto a la derecha C({p_izq}).

 Idea recursiva:

 Choripanes (i, k, ultN) | C({p_ULTN}) si K == 0
                         | INF si i == N
                         | min(Choripanes (i+1, k-1, i) + C({p_ULTN, p_i}), Choripanes (i+1, k, ultN))

 Sabemos por enunciado que p(i) < p(i+1), por lo tanto, ultN > i es una "bandera" para indicar que todavía no se colocó ninguna proveeduría.

 Así, inicializamos con Choripanes(0, K, N-1), y agregamos las siguientes podas: K == N, dejar de buscar si quedan más proveedurías que puestos

*/

int C(int ultN, int i, vector<int>& x) {
    int sum = 0;
    for (int k = ultN * (ultN < i); k <= i; ++k) {
        sum += min(abs(x[ultN] - x[k]), abs(x[i] - x[k]));
    }
    return sum;
}

int Choripanes(int i, int k, int ultN, vector<int>& x, vector<vector<vector<int>>>& memo) {
    int N = x.size();

    if (k == 0) {
        int sum = 0;
        for (int j = ultN; j < N; ++j) {
            sum += abs(x[ultN] - x[j]);
        }
        memo[k][ultN][i] = sum;

        return memo[k][ultN][i];
    }

    if (i == N || k > x.size()-i) {
        memo[k][ultN][i] = INF;
        return memo[k][ultN][i];
    }

    if (memo[k][ultN][i] != -1) {
        return memo[k][ultN][i];
    }

    memo[k][ultN][i] = min(Choripanes(i + 1, k - 1, i, x, memo) + C(ultN, i, x), Choripanes(i + 1, k, ultN, x, memo));

    return memo[k][ultN][i];
}

/*

 Para rastrear menor cadena lexicográfica, volvemos sobre nuestros pasos en la matriz, ya teniendo y pudiendo comparar sobre
 los costos que se fueron acumulando.

*/

void buscarcadena(int k, int ultN, int i, vector<int>& x, vector<vector<vector<int>>>& memo) {
    while (k > 0) {
        if (memo[k][ultN][i] == (memo[k - 1][i][i + 1] + C(ultN, i, x))) {
            cout << x[i] << " ";
            k--;
            ultN = i;
            i++;
        }
        else {
            i++;
        }
    }
    cout << endl;
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int N, K;
        cin >> N >> K;
        vector<int> puestos_ciudad(N);
        for (int i = 0; i < N; ++i) {
            cin >> puestos_ciudad[i];
        }
        if (K == N) {
            cout << 0 << endl;
            for (int puestoK : puestos_ciudad) {
                cout << puestoK << " ";
            }
            cout << endl;
        }
        else {
            vector<vector<vector<int>>> memo(K + 1, vector<vector<int>>(N+1, vector<int>(N+1, -1)));
            int resultado = Choripanes(0, K, N-1, puestos_ciudad, memo);
            cout << resultado << endl;
            buscarcadena(K, N-1, 0, puestos_ciudad, memo);
        }
    }

    return 0;
}
