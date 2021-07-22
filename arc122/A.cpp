#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

const long long MOD = 1000000000 + 7;

int main() {
    int N;
    cin >> N;

    VLL A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    long long ans = 0;
    VVLL dp(N, VLL(2));
    VVLL comb(N, VLL(2));
    dp[0][0] = A[0];
    comb[0][0] = 1;

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                if (j == 1 && k == 1) {
                    continue;
                }

                dp[i][k] += dp[i-1][j];
                comb[i][k] += comb[i-1][j];
                dp[i][k] %= MOD;
                comb[i][k] %= MOD;
            }
        }

        for (int k = 0; k < 2; ++k) {
            if (k == 0) {
                dp[i][k] += comb[i][k] * A[i];
            } else {
                dp[i][k] -= comb[i][k] * A[i];
            }
            dp[i][k] %= MOD;
        }
    }

    ans = (dp[N-1][0] + dp[N-1][1])%MOD;
    ans = (ans+MOD)%MOD;

    cout << ans << endl;
    return 0;
}