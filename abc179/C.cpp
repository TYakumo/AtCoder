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
using VB = vector <bool>;

int main() {
    int N;
    // A*B = N-C
    cin >> N;

    VLL ans(N+1);
    VB notPrime(N+1);

    long long res = 0;
    ans[1] = 1;

    for (int v = 2; v < N; ++v) {
        if (notPrime[v]) {
            continue;
        } else {
            ans[v] = 2;
        }

        for (int val = v*2; val < N; val += v) {
            int tmpv = val / v;
            int cnt = 1;
            notPrime[val] = true;

            while (tmpv%v == 0) {
                tmpv /= v;
                ++cnt;
            }

            ans[val] = ans[tmpv] * (1+cnt);
        }
    }

    for (int i = 1; i < N; ++i) {
        res += ans[i];
    }

    cout << res << endl;

    return 0;
}