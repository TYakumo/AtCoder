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

struct GCDInfo {
    long long x;
    long long y;
    long long g;
    GCDInfo(long long px, long long py, long long pg) : x(px), y(py), g(pg) {
    }
};

GCDInfo gcd(long long a, long long b) {
    if (b == 0) {
        return GCDInfo(1, 0, a);
    }

    // ax+by = g
    // bx'+(a-a/b*b)y' = g
    GCDInfo v = gcd(b, a%b);
    return GCDInfo(v.y, v.x-(a/b)*v.y, v.g);
}

// Get a * x mod p = 1
long long findInv(long long a, long long p) {
    return gcd(a, p).x;
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    const long long MOD = 1000000000 + 7;
    vector <long long> fact(M+1);
    fact[0] = 1;

    for (int v = 1; v <= M; ++v) {
        fact[v] = (fact[v-1] * v) % MOD;
    }

    // K => the Same in A & B (P M K)
    // N-K in A or B (P M-K N-K)

    auto getP = [&fact, &MOD] (long long a, long long b) { return (fact[a] * findInv(fact[a-b], MOD)) % MOD; };
    auto getC = [&fact, &MOD, &getP] (long long a, long long b) { return getP(a, b) * findInv(fact[b], MOD) % MOD; };

    long long ans = 0;
    long long sign = 1;

    for (int k = 0; k <= N; ++k) {
        long long combK = getC(M, k) * getP(N, k) % MOD;
        long long combA = getP(M-k, N-k) % MOD;

        ans += sign * (combK*combA%MOD) * combA % MOD;
        sign *= -1;
        ans %= MOD;
    }

    cout << (ans%MOD + MOD) % MOD << endl;

    return 0;
}