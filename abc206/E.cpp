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


int main() {
    long long ans = 0;
    int L;
    int R;
    cin >> L >> R;

    VI primes;
    int UPPER = R+10;
    VI np(UPPER);
    VI factCnt(UPPER, 0);
    VI onlyOne(UPPER, 1);

    for (long long v = 2; v < np.size(); ++v) {
        if (np[v] == 0) {
            primes.push_back(v);
            factCnt[v] = 1;
        }

        for (int j = 0; j < primes.size() && v*primes[j] < np.size(); ++j) {
            long long newv = v*primes[j];
            np[newv] = 1;
            factCnt[newv] = factCnt[v]+1;
            onlyOne[newv] = onlyOne[v];

            if (v%primes[j] == 0) {
                onlyOne[newv] = 0;
                break;
            }
        }
    }

    for (long long g = 2; g <= R; ++g) {
        long long from = max(1LL, (L+g-1)/g);
        long long to = R/g;

        long long cho = to-from+1;
        long long sign = factCnt[g]%2 == 0 ? -1 : 1;

        if (cho >= 1 && onlyOne[g]) {
            ans += sign * cho * (cho-1) / 2;
        }

        if (from <= 1 && to >= from) {
            ans -= (to-1);
        }
    }

    cout << ans*2 << endl;

    return 0;
}