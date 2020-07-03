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

long long fastPow(long long v, long long p) {
    if (p == 0) {
        return 1;
    }

    long long hp = fastPow(v, p/2);
    hp *= hp;
    hp %= MOD;

    if (p%2) {
        hp *= v;
        hp %= MOD;
    }

    return hp;
}

int main() {
    string S;
    int K;
    cin >> K >> S;

    long long N = S.size();
    // a^(p-1) mod P = 1
    long long invP = fastPow(26, MOD-2);
    long long val = fastPow(26, K);
    long long ans = 0;
    long long mul = 1;

    for (int k = 0; k <= K; ++k) {
        // H (K N)
        // C(K+N-1 N-1)
        ans += mul * val;
        ans %= MOD;

        mul *= (k+N);
        mul %= MOD;
        mul *= fastPow(k+1, MOD-2);
        mul %= MOD;

        val *= invP;
        val %= MOD;

        val *= 25;
        val %= MOD;
    }

    cout << ans << endl;

    return 0;
}