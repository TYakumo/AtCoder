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
    return GCDInfo(v.y%(b/v.g), (v.x-(a/b)*v.y)%(a/v.g), v.g);
}

// Get a * x mod p = g
long long findInv(long long a, long long p) {
    return gcd(a, p).x;
}

int main() {
    int T;
    cin >> T;

    for (int tc = 0; tc < T; ++tc) {
        long long X;
        long long Y;
        long long P;
        long long Q;

        cin >> X >> Y >> P >> Q;
        long long best = -1;

        long long PQ = P+Q;
        long long XY2 = 2*X+2*Y;
        for (long long y = 0; y < Y; ++y) {
            for (long long q = 0; q < Q; ++q) {
                // t % (2X+2Y) = X+y
                // t %  (P+Q) = P+q
                if (q == 0 || y == 0) {
                    // (2X+2Y)*g.x + (P+Q)*g.y = g.g
                    GCDInfo g = gcd(XY2, PQ);
                    long long diff = (P+q)-(X+y);
                    long long remain = (X+y)%g.g;

                    if (diff % g.g == 0) {
                        long long r1 = X+y-remain;
                        long long r2 = P+q-remain;
                        long long mul1 = r1/g.g;
                        long long mul2 = r2/g.g;
                        long long lcm = PQ*XY2/g.g;
                        long long PQg = PQ/g.g;
                        long long XY2g = XY2/g.g;
                        long long gy = findInv(PQ/g.g, XY2/g.g);
                        long long gx = findInv(XY2/g.g, PQ/g.g);
                        long long val = PQ*(gy*mul1%XY2g)%lcm + XY2*(gx*mul2%PQg)%lcm + remain;
                        val = (val%lcm + lcm) % lcm;

                        if (val%(XY2) == X+y && val%PQ == P+q) {
                            if (best <= 0 || val < best) {
                                best = val;
                            }
                        }
                    }
                }
            }
        }

        if (best <= 0) {
            cout << "infinity" << endl;
        } else {
            cout << best << endl;
        }
    }

    return 0;
}