#include <iostream>
#include <vector>

using namespace std;

int cantBellotas(int t, int h, int f, const vector<vector<int>>& bosque) {
    vector<vector<int>> memo(t, vector<int>(h + 1, 0));
    vector<int> maximoAlturas((h+1), 0);
    for (int altura = 0; altura <= h; altura++) {
        for (int arbol = 0; arbol < t; arbol++) {
            if (altura-f >= 0) memo[arbol][altura] = max(memo[arbol][altura - 1], maximoAlturas[altura-f]) + bosque[arbol][altura];
            else if (altura == 0) memo[arbol][altura] = bosque[arbol][altura];
            else memo[arbol][altura] = memo[arbol][altura - 1] + bosque[arbol][altura];
            maximoAlturas[altura] = max(maximoAlturas[altura], memo[arbol][altura]);
        }
    }
    return maximoAlturas[h];
}

int main() {
    int c;
    scanf("%d", &c);

    while (c--) {
        int t, h, f;
        scanf("%d %d %d", &t, &h, &f);

        vector<vector<int>> bosque(t, vector<int>(h + 1, 0));
        for (int i = 0; i < t; i++) {
            int a;
            scanf("%d", &a);
            for (int j = 0; j < a; j++) {
                int n;
                scanf("%d", &n);
                bosque[i][n]++;
            }
        }

        printf("%d\n", cantBellotas(t, h, f, bosque));
    }

    return 0;
}