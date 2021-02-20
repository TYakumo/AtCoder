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

int main() {
    int N;
    long long X;
    cin >> N >> X;

    VLL A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    const long long INF = 1000000000LL * 1000000000LL;
    long long best = INF;
    for (int c = 1; c <= N; ++c) {
        VVLL dp(c+1, VLL(c, -1));
        dp[0][0] = 0;

        for (int i = 0; i < N; ++i) {
            for (int a = min(i, c-1); a >= 0; --a) {
                for (int j = 0; j < c; ++j) {
                    if (dp[a][j] >= 0) {
                        int newc = (j+A[i])%c;
                        long long newsum = dp[a][j]+A[i];

                        dp[a+1][newc] = max(dp[a+1][newc], newsum);
                    }
                }
            }
        }

        long long modv = X%c;
        if (dp[c][modv] >= 0) {
            best = min(best, (X-dp[c][modv])/c);
        }
    }

    cout << best << endl;

    return 0;
}