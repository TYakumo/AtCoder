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

const long long MOD = 998244353;

long long powMod(long long n, long long p, long long m) {
    if (p == 0) {
        return 1;
    }

    long long hp = powMod(n, p/2, m);
    long long ret = hp*hp%m;

    if (p%2 == 1) {
        ret = (ret*n)%m;
    }

    return ret;
}

using VLL = vector <long long>;

int main() {
    int N;
    int M;
    int K;
    cin >> N >> M >> K;
    // min Bj >= max Ai

    int maxV = max(N, M);
    VLL fact(maxV+1);
    fact[0] = 1;
    for (int v = 2; v <= maxV; ++v) {
        fact[v] = fact[v-1] * v % MOD;
    }

    long long ans = 0;
    if (N == 1) {
        ans =  powMod(K, M, MOD) % MOD;
    } else if (M == 1) {
        ans =  powMod(K, N, MOD) % MOD;
    } else {
        for (long long sp = 1; sp <= K; ++sp) {
            // sp^N * N! * (K-sp+1)^M * M!
            long long cp = K-sp+1;

            long long comb = (powMod(sp, N, MOD)-powMod(sp-1, N, MOD)) % MOD;
            long long comb2 = powMod(K-sp+1, M, MOD) % MOD;
            ans += comb*comb2%MOD;
            ans %= MOD;
        }
    }

    cout << (ans+MOD)%MOD << endl;

    return 0;
}