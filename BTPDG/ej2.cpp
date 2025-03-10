#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct descontento_tiempo {
    int m_i;
    int c_i;

    bool operator<(const descontento_tiempo& other) const {
        return (1.0 * m_i / c_i < 1.0 * other.m_i / other.c_i);
    }

};

unsigned long long minimo_descontento_general(const vector<int>& M, const vector<int>& C) {
    unsigned long long acumulado = 0;
    unsigned long long total = 0;

    vector<descontento_tiempo> info_alumnos;
    for (int i = 0; i < M.size(); ++i) {
        info_alumnos.push_back({M[i], C[i]});
    }

    sort(info_alumnos.begin(), info_alumnos.end());

    for (auto & info_alumno : info_alumnos) {
        acumulado += info_alumno.m_i;
        total += info_alumno.c_i * acumulado;
        total %= 1000000007;
    }

    return total;

}

int main() {
    int c;
    cin >> c;

    while (c--) {

        int N;
        cin >> N;

        vector<int> M(N, 0);
        vector<int> C(N, 0);

        for (int i=0; i<N; i++)
            cin >> M[i];

        for (int j=0; j<N; j++)
            cin >> C[j];

        cout << minimo_descontento_general(M, C) << endl;
    }

    return 0;

}
