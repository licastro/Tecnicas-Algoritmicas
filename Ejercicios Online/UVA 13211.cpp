#include <iostream>
#include <vector>

using namespace std;

void floydWarshall(vector<vector<int>>& energia, vector<int>& orden, long long int& res, int n) {
    long long int acum = 0;
    for (int ok = n - 1; ok > -1; ok--) {
        int k = orden[ok];
        for (int oi=0; oi<n; oi++) {
            int i = orden[oi];
            for (int oj=0; oj<n; oj++) {
                int j = orden[oj];
                if (energia[i][k] + energia[k][j] < energia[i][j]) {
                    if (oi > ok && oj > ok) {
                        acum += -energia[i][j] + energia[i][k] + energia[k][j];
                    }
                    energia[i][j] = energia[i][k] + energia[k][j];
                }
            }
        }
        res += acum;
        for (int obase = ok; obase < n; obase++) {
            int base = orden[obase];
            res += energia[k][base] + energia[base][k];
            acum += energia[k][base] + energia[base][k];
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<vector<int>> energia(n, vector<int>(n));
        vector<int> orden;
        int f;
        long long int res = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &energia[i][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            scanf("%d", &f);
            orden.push_back(f);
        }

        floydWarshall(energia, orden, res, n);

        printf("%lld\n", res);
    }

    return 0;
}
