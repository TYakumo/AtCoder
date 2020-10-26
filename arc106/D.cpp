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
using VLL = vector <long long>;
using VVLL = vector <VLL>;

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

long long modPow(long long x, long long p) {
    if (p == 0) {
        return 1;
    }

    long long hf = modPow(x, p/2);
    long long ret = hf*hf % MOD;

    if (p&1) {
        ret = ret * x % MOD;
    }

    return ret;
}

int main() {
    int N;
    int K;

    cin >> N >> K;
    VLL A(N);
    VLL fact(K+1);
    VVLL sum(K+1, VLL(N+1));

    fact[0] = 1;
    for (int i = 1; i <= K; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }

    for (int i = 0; i < N; ++i) {
        cin >> A[i];

        long long PA = 1;
        for (int k = 0; k <= K; ++k) {
            sum[k][i] = PA;

            if (i) {
                sum[k][i] += sum[k][i-1];
                sum[k][i] %= MOD;
            }

            PA = (PA * A[i]) % MOD;
        }
    }

    auto getC = [&fact] (int a, int b) {
        return fact[a] * findInv(fact[b], MOD) % MOD * findInv(fact[a-b], MOD) % MOD;
    };

    for (int x = 1; x <= K; ++x) {
        long long tot = 0;
        // for (int l = 0; l < N-1; ++l) {
        //     // Al^X + C(X, X-1)Al^X-1 Ar^1 + C(X, X-2) Al ...
        //     for (int k = x; k >= 0; --k) {
        //         int cp = x - k;
        //         long long targetSum = sum[cp][N-1] - sum[cp][l];
        //         long long res = modPow(A[l], k) * getC(x, k) % MOD * targetSum % MOD;
        //         tot = (tot + res) % MOD;
        //     }
        // }

        // C(x, k) * [A1^k*(A2^cp+A3^cp ...) + A2^k*(A3^cp+A4^cp ...) + (A3^k) * (A4^cp+A5^cp ...)] ...
        // for Al => Al^cp*(A1^k+....A(l-1)^k) or Al^k*(A(l+1)^cp+....AN^cp)
        // when k' = cp, C(x, k') = C(x, cp) = C(x, k)
        // Al => C(x, k')*[Al^cp'*(A1^k'+....A(l-1)^k') + Al^k'*(A(l+1)^cp'+....AN^cp')]
        // Al => C(x, k')*[Al^k*(A1^cp+....A(l-1)^cp) - Al^cp*(A(l+1)^k...AN^k)]
        // 2 * Sum => C(x, k)*[Al^k(Sigma A^cp - Al^cp) - Al^cp(Sigma A^k - A^k)]

        // Sigma[C(x, k)]*A^x = 2^x * Sum(A^x)
        // 2Sum + 2^x * Sum(A^x) = Conv
        // Sum = [Conv - 2^x * Sum(A^x)] / 2

        for (int k = x; k >= 0; --k) {
            int cp = x - k;
            long long res = sum[k][N-1] * sum[cp][N-1] % MOD;
            res = res * getC(x, k) % MOD;
            tot = (tot + res) % MOD;
        }

        tot -= sum[x][N-1] * modPow(2, x) % MOD;
        tot = (tot * findInv(2, MOD)) % MOD;

        cout << (tot+MOD)%MOD << endl;
    }

    return 0;
}