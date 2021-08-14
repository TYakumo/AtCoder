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

long long solve(UMLL& ans, long long n) {
    if (n == 0) {
        return 0;
    }

    if (ans.count(n)) {
        return ans[n];
    }

    long long ret = 5;
    long long t = n/10;
    long long r = n%10;

    for (long long m = 1; m <= 4; ++m) {
        long long low = m;
        long long up = m * 3;

        if (r >= low && r <= up && solve(ans, t) <= m) {
            ret = min(ret, m);
        }

        if (up >= 10 && t > 0) {
            long long nlow = 0;
            long long nup = up-10;
            if (r >= nlow && r <= nup && solve(ans, t-1) <= m) {
                ret = min(ret, m);
            }
        }
    }

    return ans[n] = ret;
}

int main() {
    int T;
    cin >> T;
    UMLL ans;

    while (T--) {
        long long N;
        cin >> N;
        cout << solve(ans, N) << endl;
    }

    return 0;
}