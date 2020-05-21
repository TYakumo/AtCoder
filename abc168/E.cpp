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

const long long MOD = 1000000007;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

void normalize(long long& A, long long &B) {
    long long g = gcd(A, B);

    if (g != 0) {
        A /= g;
        B /= g;
    }

    if (A < 0) {
        A = -A;
        B = -B;
    } else if (A == 0) {
        if (B < 0) {
            B = -B;
        }
    }
}

long long twoPowMod(long long n) {
    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return 2;
    }

    long long half = twoPowMod(n/2);
    long long ret = half*half % MOD;

    if (n%2) {
        ret *= 2;
        ret %= MOD;
    }

    return ret;
}

int main() {
    int N;
    cin >> N;
    map < pair<long long, long long>, long long> cnt;
    long long spec = 0;

    for (int i = 0; i < N; ++i) {
        long long A;
        long long B;
        cin >> A >> B;
        normalize(A, B);

        if (A != 0 || B != 0) {
            ++cnt[make_pair(A, B)];
        } else {
            ++spec;
        }
    }

    auto iter = cnt.begin();
    long long ans = 1;

    while (iter != cnt.end()) {
        long long A = iter->first.first;
        long long B = iter->first.second;
        long long OB = -A;
        long long OA = B;
        normalize(OA, OB);

        long long res = 0;

        if (OA != A || OB != B) { // avoid mirror
            res += twoPowMod(cnt[make_pair(A, B)]);
            res += twoPowMod(cnt[make_pair(OA, OB)]);
            --res; // empty set
        } else {
            res = cnt[make_pair(A, B)]+1;
        }

        res = (res + MOD)%MOD;
        cnt[make_pair(A, B)] = cnt[make_pair(OA, OB)] = 0;

        ans *= res;
        ans %= MOD;

        ++iter;
    }

    cout << ((ans+MOD-1) + spec)%MOD << endl;
    return 0;
}