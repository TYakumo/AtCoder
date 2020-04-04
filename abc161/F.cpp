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

int main() {
    long long N;
    long long tmp;
    cin >> N;

    // factorization
    tmp = N-1;
    long long sq = sqrt(N-1);
    long long ans = 1;

    for (int n = 2; n <= sq; ++n) {
        int cnt = 0;
        while (tmp%n == 0) {
            tmp /= n;
            ++cnt;
        }

        if (cnt) {
            ans *= (cnt+1);
        }
    }

    if (tmp != 1) {
        ans *= 2;
    }

    // no 1
    --ans;

    tmp = N;
    // N/K... - K = 1
    sq = sqrt(N);

    for (int n = 2; n <= sq; ++n) {
        if (N%n == 0) {
            long long tmp2 = N;

            while (tmp2 % n == 0) {
                tmp2 /= n;
            }

            if (tmp2%n == 1) {
                ++ans;
            }
        }
    }

    cout << ans + 1 << endl;

    return 0;
}