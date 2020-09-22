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
#include <atcoder/math>
using namespace std;
using namespace atcoder;

using VLL = vector <long long>;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a%b);
}

int main() {
    long long N;
    cin >> N;

    if (N == 1) {
        cout << 1 << endl;
        return 0;
    }

    // [(k) * (k+1) / 2] % N == 0
    // (k) * (k+1) % (2*N) == 0
    // k*(k+1) == 2*t*N where t >= 1
    // (ax) * (by) = 2*t*N
    // a*b = t, and x*y = 2*N
    VLL factors;
    long long rt = sqrt(2*N);

    for (int v = 2; v <= rt; ++v) {
        if (2*N % v == 0) {
            long long div = 2*N/v;

            // k = ax, (k+1) = by, and k co-prime k+1
            if (gcd(div, v) == 1) {
                factors.push_back(v);
                factors.push_back(div);
            }
        }
    }

    long long ans = 2*N;

    for (int i = 0; i < factors.size(); ++i) {
        VLL r = {0, -1};
        VLL m = {factors[i], 2*N / factors[i]};
        long long lcm = 2*N;

        // k mod x = 0
        // k mod y = -1
        pair<long long, long long> res = crt(r, m);

        if (res.first != 0 || res.second != 0) {
            res.first = res.first == 0 ? lcm : res.first;
            ans = min(ans, res.first);
        }
    }

    cout << ans << endl;

    return 0;
}