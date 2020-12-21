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

    // S+i*K = 0 mod N => i*K = -S mod N
    // i = -S/K mod N

    int T;
    cin >> T;

    while (T--) {
        long long N;
        long long S;
        long long K;
        cin >> N >> S >> K;
        long long g = gcd(gcd(N, S).g, K).g;
        N /= g;
        S /= g;
        K /= g;

        if (gcd(N, K).g == 1) { // must have solution
            long long inv = findInv(K, N);
            long long mul = N-S;
            long long ans = (mul*inv)%N;
            cout << (ans+N)%N << endl;
        } else {
            if (S == 0) {
                cout << 0 << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }

    return 0;
}