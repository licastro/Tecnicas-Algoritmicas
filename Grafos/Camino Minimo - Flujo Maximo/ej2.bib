#include <iostream>
#include <vector>

using namespace std;

bool eliminarRedundancia(int N, vector<vector<int>>& latencias, vector<vector<int>>& distancias) {

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {

                int alternativa = latencias[i][k] + latencias[k][j];

                if (latencias[i][j] > alternativa) {
                    return false;
                }

                if (latencias[i][j] == alternativa && i!=k && k!=j) {
                    distancias[i][j] = 1e9;
                    distancias[j][i] = 1e9;
                }

            }
        }
    }

    return true;
}

bool floyd(int N, vector<vector<int>>& distancias) {

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                if (distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                    distancias[j][i] = distancias[i][j];
                }
            }
        }
    }

    return true;
}

int main() {

    int c;
    scanf("%d", &c);

    while (c--) {
        int N;
        scanf("%d", &N);

        vector<vector<int>> latencias(N, vector<int>(N, 0));
        vector<vector<int>> distancias(N, vector<int>(N, 1));
        distancias[0][0] = 0;

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int l_ij;
                scanf("%d", &l_ij);
                latencias[i][j] = l_ij;
                latencias[j][i] = l_ij;
            }
            distancias[i][i] = 0;
        }

        if (eliminarRedundancia(N, latencias, distancias)) {
            floyd(N, distancias);
            printf("POSIBLE\n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%d", distancias[i][j]);
                    printf(" ");
                }
                printf("\n");
            }
        }
        else printf("IMPOSIBLE\n");

    }

    return 0;
}
