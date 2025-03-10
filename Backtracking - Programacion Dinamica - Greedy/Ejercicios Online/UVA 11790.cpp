#include <iostream>
#include <vector>

using namespace std;

void incdec(int i, int ultI, vector<vector<int>>& memoI, vector<vector<int>>& memoD, const vector<int>& height, const vector<int>& width, int n) {

    if (i == n) {
        memoI[i][ultI + 1] = 0;
        memoD[i][ultI + 1] = 0;
    }

    if (memoI[i][ultI + 1] == -1 || memoD[i][ultI + 1] == -1) {

        incdec(i + 1, ultI, memoI, memoD, height, width, n);
        memoI[i][ultI + 1] = memoI[i+1][ultI + 1];
        memoD[i][ultI + 1] = memoD[i+1][ultI + 1];

        if (ultI == -1 || height[i] != height[ultI]) {
            incdec(i + 1, i, memoI, memoD, height, width, n);
            if (ultI == -1 || height[i] > height[ultI]) memoI[i][ultI + 1] = max(memoI[i][ultI + 1], memoI[i+1][i+1] + width[i]);
            else if (ultI == -1 || height[i] < height[ultI]) memoD[i][ultI + 1] = max(memoD[i][ultI + 1], memoD[i+1][i+1] + width[i]);
        }
    }
}

int main() {

    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; ++i) {

        int n;
        scanf("%d", &n);

        vector<int> heights(n);
        vector<int> widths(n);

        for (int j = 0; j < n; ++j) scanf("%d", &heights[j]);
        for (int j = 0; j < n; ++j) scanf("%d", &widths[j]);

        vector<vector<int>> memoI(n + 1, vector<int>(n + 2, -1));
        vector<vector<int>> memoD(n + 1, vector<int>(n + 2, -1));

        incdec(0, -1, memoI, memoD, heights, widths, n);

        printf("Case %d. ", i);

        if (memoI[0][0] >= memoD[0][0]) printf("Increasing (%d). Decreasing (%d).\n", memoI[0][0], memoD[0][0]);
        else printf("Decreasing (%d). Increasing (%d).\n", memoD[0][0], memoI[0][0]);
    }

    return 0;
}
