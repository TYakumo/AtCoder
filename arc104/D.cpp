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
    int K;
    long long M;
    cin >> N >> K >> M;

    VVLL dp(N+1, VLL(N*N*K));
    dp[0][0] = 1;
    int theMax = 0;

    for (int n = 1; n <= N; ++n) {
        theMax += K*n;

        for (int k = 0; k <= theMax; ++k) {
            // dp[i][val] = Sigma i = 0 ... K dp[i-1][val-i*n] = dp[i-1][val] + dp[i][val-n] - dp[i-1][val-n*(K+1)];
            dp[n][k] = dp[n-1][k];

            if (k-n >= 0) {
                dp[n][k] += dp[n][k-n];
            }

            if (k-n*(K+1) >= 0) {
                dp[n][k] -= dp[n-1][k-n*(K+1)];
            }

            dp[n][k] %= M;
        }
    }

    for (int n = 1; n <= N; ++n) {
        int left = n-1;
        int right = N-n;

        long long ans = K;

        if (left != 0 && right != 0) {
            for (int v = 1; v <= theMax; ++v) {
                ans += dp[left][v] * dp[right][v] % M * (K+1) % M;
            }
        }

        ans = (ans%M + M) % M;

        cout << ans << endl;
    }

    return 0;
}