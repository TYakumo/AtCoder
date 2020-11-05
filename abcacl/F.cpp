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
#include <atcoder/all>
using namespace std;
using namespace atcoder;

const long long MOD = 998244353;
using VI = vector <int>;

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

long long fastPow(long long a, long long p) {
    if (p == 0) {
        return 1;
    }

    long long hf = fastPow(a, p/2);
    long long ret = hf*hf%MOD;

    if (p%2) {
        ret = (ret * a) % MOD;
    }

    return ret;
}

using VLL = vector <long long>;
using VVLL = vector <VLL>;

int main() {
    int N;
    cin >> N;

    VI h(2*N);
    VI cho;

    for (int i = 0; i < 2*N; ++i) {
        cin >> h[i];
    }

    sort(h.begin(), h.end());
    for (int i = 0; i < h.size(); ) {
        int j = i;

        while (j+1 < h.size() && h[i] == h[j+1]) {
            ++j;
        }

        int len = (j-i+1);

        if (len >= 2) {
            cho.push_back(len);
        }

        i = j+1;
    }

    int UPPER = h.size()+5;
    VLL fact(UPPER);

    fact[0] = 1;
    for (int i = 1; i < UPPER; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
    }

    auto getC = [&fact](int a, int b) {
        return fact[a] * findInv(fact[b], MOD) % MOD * findInv(fact[a-b], MOD) % MOD;
    };

    auto getP = [&fact](int a, int b) {
        return fact[a] * findInv(fact[b], MOD) % MOD;
    };

    auto getComb = [&fact, &getP](int n) {
        return getP(2*n, n)*fastPow(findInv(2, MOD), n)%MOD;
    };

    sort(cho.begin(), cho.end());
    deque <VLL> result;
    result.push_back({1});

    for (int i = 0; i < cho.size(); ++i) {
        VLL rvec;

        for (int j = 0; j <= cho[i]; j += 2) {
            rvec.push_back(getC(cho[i], j)*getComb(j/2)%MOD);
        }

        result.push_back(rvec);
    }

    while (result.size() > 1) { // can be further optimized to be Huffmann coding merge
        VLL v = convolution(result[0], result[1]);
        result.pop_front();
        result.pop_front();

        if (result.empty() || v.size() > result.front().size()) {
            result.push_back(v);
        } else {
            result.push_front(v);
        }
    }

    long long ans = 0;
    long long sign = 1;

    for (int p = 0; p < result.front().size(); ++p) {
        int remain = N - p;
        // notice (Xp, Xn-p) counts twice except p=0 and p=maxp
        // like (1, 3) can appear in both result.front()[p] or getComb(remain), but they are the same
        long long res = getComb(remain) * result.front()[p] % MOD;
        ans = (ans + res*sign) % MOD;
        sign *= -1;
    }

    cout << (ans+MOD) % MOD << endl;


    return 0;
}