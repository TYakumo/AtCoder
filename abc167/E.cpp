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

long long mpow(long long b, int p) {
    if (p == 0) {
        return 1;
    }

    if (p == 1) {
        return b%MOD;
    }

    long long half = mpow(b, p/2);
    long long ret = half*half%MOD;

    if (p%2 == 1) {
        ret *= b;
        ret %= MOD;
    }

    return ret;
}

int main() {
    int N;
    int M;
    int K;

    cin >> N >> M >> K;
    long long ans = 0;

    long long comb = 1;
    for (int i = 0; i <= K; ++i) {
        int p = N-i-1; // K <= N-1, p >= 0

        ans += M * mpow(M-1, p) % MOD * comb;
        ans %= MOD;

        comb *= (N-i-1);
        comb %= MOD;
        // comb *= pow(i+1, MOD-2);
        comb *= findInv(i+1, MOD);
        comb %= MOD;
    }

    ans = (ans+MOD) % MOD;
    cout << ans << endl;
    return 0;
}