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

const long long MOD = 1000000000LL + 7;

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

    long long N;
    long long M;
    long long K;
    cin >> N >> M >> K;

    if (N > M+K) {
        cout << 0 << endl;
        return 0;
    }

    long long TOT = N+M;
    VLL fact(TOT+1);
    VLL factInv(TOT+1);
    fact[0] = 1;
    factInv[0] = 1;

    for (long long v = 1; v <= TOT; ++v) {
        fact[v] = (fact[v-1]*v)%MOD;
        factInv[v] = findInv(fact[v], MOD);
    }

    auto CComb = [&fact, &factInv](long long a, long long b) { return a < 0 || b < 0 || b > a ? 0 : fact[a]*factInv[b]%MOD*factInv[a-b]%MOD; };
    // no constraint => C (N+M) N
    // (-K-1, K+1) to (M, N) => N+K+1+(M-K-1), M+K+1
    long long ans = (CComb(N+M, N) - CComb(N+M, M+K+1))%MOD;

    cout << (ans+MOD)%MOD << endl;
    return 0;
}