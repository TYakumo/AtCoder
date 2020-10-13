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

const long long MOD = 1000000000 + 7;
long long modPow(long long n, long long p){
    if (p == 0) {
        return 1;
    }

    long long hf = modPow(n, p/2);
    long long ret = hf*hf % MOD;

    if (p%2 != 0) {
        ret = (ret * n) % MOD;
    }

    return ret;
}


int main() {
    int H;
    int W;
    long long tot = 0;

    cin >> H >> W;

    vector <string> S(H);

    for (int i = 0; i < H; ++i) {
        cin >> S[i];

        for (int j = 0; j < W; ++j) {
            if (S[i][j] != '#') {
                ++tot;
            }
        }
    }

    long long ans = 0;
    VVLL dp(H, VLL(W, -3)); // every cell will be counting self for 4 times.

    for (int i = 0; i < H; ++i) {
        long long acc = 0;
        for (int j = 0; j < W; ++j) {
            if (S[i][j] != '#') {
                ++acc;
                dp[i][j] += acc;
            } else {
                acc = 0;
            }
        }

        acc = 0;
        for (int j = W-1; j >= 0; --j) {
            if (S[i][j] != '#') {
                ++acc;
                dp[i][j] += acc;
            } else {
                acc = 0;
            }
        }
    }

    for (int j = 0; j < W; ++j) {
        long long acc = 0;
        for (int i = 0; i < H; ++i) {
            if (S[i][j] != '#') {
                ++acc;
                dp[i][j] += acc;
            } else {
                acc = 0;
            }
        }

        acc = 0;
        for (int i = H-1; i >= 0; --i) {
            if (S[i][j] != '#') {
                ++acc;
                dp[i][j] += acc;
            } else {
                acc = 0;
            }
        }
    }

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (S[i][j] != '#') {
                long long res = (modPow(2, dp[i][j]) - 1) * modPow(2, tot - dp[i][j]) % MOD;
                ans += res;
                ans %= MOD;
            }
        }
    }

    ans = (ans + MOD) % MOD;
    cout << ans << endl;

    return 0;
}