#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matrizMemoria;
vector<int> A;
int suma_max = 0;

vector<int> Registros;

int CP(int i, int res) {
    int res_columna = res + suma_max;

    if (i == A.size()) {
        matrizMemoria[i][res_columna] = res == 0;
        return matrizMemoria[i][res_columna];
    }

    if (matrizMemoria[i][res_columna] != -1) {
        return matrizMemoria[i][res_columna];
    }

    int p = CP(i + 1, res - A[i]);
    int n = CP(i + 1, res + A[i]);

    matrizMemoria[i][res_columna] = p || n;

    Registros[2*i] += p;
    Registros[2*i + 1] += n;

    return matrizMemoria[i][res_columna];
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int N, W;
        cin >> N >> W;
        A.resize(N, 0);
        suma_max += abs(W/100);
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            A[i] = x/100;
            suma_max += x/100;
        }

        matrizMemoria.assign(A.size() + 1, vector<int>(2 * suma_max + 1, -1));
        Registros.resize(N*2, 0);

        CP(0, W/100);

        for(int i = 0; i < Registros.size(); i+=2) {
            bool p = Registros[i] != 0;
            bool n = Registros[i + 1] != 0;
            if (p && n)
                cout << '?';
            else if (p && !n)
                cout << '+';
            else
                cout << '-';
        }
        cout<<endl;

        matrizMemoria.clear();
        suma_max = 0;
        A.clear();
        Registros.clear();
    }

    return 0;
}
