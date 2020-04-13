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

inline long long modpow(long long n, long long p) {
    if (p == 0) {
        return 1;
    }

    long long half = modpow(n, p/2);
    long long mul = (n-1)*(p%2) + 1;

    return half * half % MOD * mul % MOD;
}

int main() {
    int N;
    int K;

    cin >> N >> K;
    vector <long long> ans(K+1);
    long long res = 0;

    for (int g = K; g >= 1; --g) {
        long long base = K/g;

        ans[g] = modpow(base, N);

        for (int j = 2*g; j <= K; j += g) {
            ans[g] -= ans[j];
        }

        ans[g] %= MOD;
        ans[g] = (ans[g]+MOD) % MOD;
        res = (res + ans[g]*g) % MOD;
    }

    cout << res << endl;

    return 0;
}