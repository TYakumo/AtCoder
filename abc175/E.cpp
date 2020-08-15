#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
using namespace std;

using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;

int main() {
    int R;
    int C;
    int K;

    cin >> R >> C >> K;

    VVVLL dp(R, VVLL(C, VLL(4)));
    VVLL val(R, VLL(C, 0));

    for (int k = 0; k < K; ++k) {
        int r;
        int c;
        cin >> r >> c;
        --r;
        --c;
        cin >> val[r][c];
    }

    dp[0][0][0] = 0;
    dp[0][0][1] = val[0][0];

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            for (int v = 0; v < 4; ++v) {
                // go down
                if (i+1 < R) {
                    if (val[i+1][j] > 0) {
                        dp[i+1][j][1] = max(dp[i+1][j][1], dp[i][j][v] + val[i+1][j]);
                    }

                    dp[i+1][j][0] = max(dp[i+1][j][0], dp[i][j][v]);
                }

                // go right
                if (j+1 < C) {
                    if (val[i][j+1] > 0 && v < 3) {
                        dp[i][j+1][v+1] = max(dp[i][j+1][v+1], dp[i][j][v] + val[i][j+1]);
                    }

                    dp[i][j+1][v] = max(dp[i][j+1][v], dp[i][j][v]);
                }
            }
        }
    }

    long long best = 0;

    for (int v = 0; v <= 3; ++v) {
        best = max(best, dp[R-1][C-1][v]);
    }

    cout << best << endl;

    return 0;
}