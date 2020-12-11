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
const long long MOD = 1000000000LL + 7;

inline long long modpow(long long n, long long p) {
    if (p == 0) {
        return 1;
    }

    long long half = modpow(n, p/2);
    long long mul = (n-1)*(p%2) + 1;

    return half * half % MOD * mul % MOD;
}

// Get a * x mod p = 1
long long findInv(long long a, long long p) {
    return modpow(a, p-2);
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    VLL A(N);
    long long S = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        S += A[i];
    }

    // (5, 4) = 5
    // 3, 1 vs 2, 2
    // (4, 3) x (1, 1), (3, 3) x (2, 1) = 4 + 2
    // (3, 2) x (2, 2), (2, 2) x (3, 2) = 6
    // (3 2) (1 1) (1 1) = 3, (2 2) (2 1) (1 1) = 2, (2 2) (1 1) (2 1) = 2, 3+4 = 7

    // looks like M => N piles = (M+N-1, S+N-1) = (M+N-1, M-S)
    // Sigma (m+N-1, S+N-1) = (M+N, S+N)

    long long ans = 1;

    for (long long v = 1; v <= S+N; ++v) {
        long long p = N+M-v+1;
        ans = (ans*p)%MOD;
        ans = (ans*findInv(v, MOD))%MOD;
    }

    cout << (ans+MOD)%MOD << endl;

    return 0;
}