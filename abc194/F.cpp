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

const long long MOD = 1000000000 + 7;
using VI = vector <int>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;

inline int toNum(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch-'A'+10;
    }
    return ch-'0';
}

int main() {
    string N;
    cin >> N;

    int K;
    cin >> K;

    VI cnt(17);
    int kind = 0;
    VVLL dp(N.size()+1, VLL(16+1));

    for (int i = 0; i < N.size(); ++i) {
        int v = toNum(N[i]);

        for (int k = 0; k < 16; ++k) {
            dp[i+1][k+1] += (dp[i][k]*(16-k) + dp[i][k+1]*(k+1));
            dp[i+1][k+1] %= MOD;
        }

        for (int n = 0; n < v; ++n) {
            if (n == 0 && i == 0) {
                continue;
            }

            if (cnt[n] == 0) {
                dp[i+1][kind+1] = (dp[i+1][kind+1] + 1) % MOD;
            } else {
                dp[i+1][kind] = (dp[i+1][kind] + 1) % MOD;
            }
        }

        // leading zero
        if (i) {
            dp[i+1][1] = (dp[i+1][1] + 15)%MOD;
        }

        if (cnt[v] == 0) {
            ++kind;
        }

        ++cnt[v];
    }

    long long ans = dp[N.size()][K];
    if (kind == K) {
        ++ans;
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}