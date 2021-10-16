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

const long long MOD = 998244353;
long long P;

void factGen(const VVLL& comp, int idx, long long mul, VLL& fact) {
    if (idx == comp.size()) {
        fact.push_back(mul);
        return ;
    }

    long long newMul = 1;
    for (long long m = 0; m <= comp[idx][1]; ++m) {
        factGen(comp, idx+1, mul*newMul, fact);
        newMul *= comp[idx][0];
    }
}

int main() {
    cin >> P;
    long long MAXV = sqrt(P) + 100;
    VLL primes;
    VI np(MAXV);

    for (long long v = 2; v < MAXV; ++v) {
        for (int j = 0; j < primes.size() && primes[j] * v < MAXV; ++j) {
            np[primes[j]*v] = 1;
            if (v % primes[j] == 0) {
                break;
            }
        }

        if (!np[v]) {
            primes.push_back(v);
        }
    }

    VVLL comp;
    long long tot = 1;
    long long tmp = P-1;
    for (int j = 0; j < primes.size(); ++j) {
        long long cnt = 0;
        while (tmp % primes[j] == 0) {
            tmp /= primes[j];
            ++cnt;
        }

        if (cnt) {
            comp.push_back({primes[j], cnt});
            tot *= (cnt+1);
        }
    }

    if (tmp > 1) {
        comp.push_back({tmp, 1});
        tot *= 2;
    }

    long long ans = 0;
    VLL fact;
    factGen(comp, 0, 1, fact);

    VLL comb(fact.size());
    sort(fact.begin(), fact.end(), greater<long long>());

    for (int i = 0; i < fact.size(); ++i) {
        long long f = fact[i];
        long long divRes = ((P-1) / fact[i])%MOD;
        long long thisComb = divRes;
        for  (int j = 0; j < i; ++j) {
            if (fact[j]%fact[i] == 0) {
                thisComb -= comb[j];
            }
        }

        // g^fact[i] = N
        // (P-1)/fact[i] = phi function cycle length
        thisComb %= MOD;
        comb[i] = thisComb;
        ans += (thisComb * divRes)%MOD;
        ans %= MOD;
    }

    ++ans;
    cout << (ans+MOD)%MOD << endl;

    return 0;
}