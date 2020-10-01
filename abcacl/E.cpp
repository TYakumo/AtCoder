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

int main() {
    int N;
    int Q;
    cin >> N >> Q;

    vector <long long> d(N+1);
    vector <long long> M(N+1);
    map <int, int> dmap;
    long long res = 1;

    M[0] = 0;
    M[1] = d[1] = 1;
    for (int i = 2; i <= N; ++i) {
        d[i] = d[i-1]*10%MOD;
        M[i] = (M[i-1] + d[i])%MOD;
    }

    res = M[N];

    dmap[1] = 1;
    dmap[N+1] = 0;

    for (int q = 0; q < Q; ++q) {
        int L;
        int R;
        int D;
        cin >> L >> R >> D;

        auto iter = dmap.lower_bound(L);
        long long OD = 0;

        if (iter->first != L) {
            --iter;
            OD = iter->second;
        } else {
            OD = iter->second;
        }

        int PP = L;
        bool breakFlag = false;

        while (true) {
            auto nextIter = iter;
            ++nextIter;

            int endPos = nextIter->first-1;

            if (nextIter->first > R) { // must be an ending pos : N
                breakFlag = true;
                endPos = R;
            }

            long long sum = (M[N-PP+1] - M[N-endPos]);
            res -= OD * sum;
            res += D * sum;
            res = (res%MOD + MOD) % MOD;

            if (breakFlag) {
                break;
            }

            iter = nextIter;
            OD = iter->second;
            PP = iter->first;
        }

        // erase (L, R)
        dmap[L] = D;
        if (dmap.find(R+1) == dmap.end()) {
            dmap[R+1] = OD;
        }
        iter = dmap.upper_bound(L);
        while (iter != dmap.end() && iter->first <= R) {
            dmap.erase(iter);
            iter = dmap.upper_bound(L);
        }

        cout << res << endl;
    }

    return 0;
}