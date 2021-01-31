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

bool checkOK(long long N, long long L) {
    N /= L;
    N -= (L-1);

    return N%2 == 0;
}

int main() {
    long long N;
    cin >> N;
    N *= 2;

    // (a0+a0+(L-1)*d) * L / 2 = N, and d = 1
    // (a0+a0+(L-1))*L = N*2
    // (-2-2+7)*8 = 12*2 => 3*8 = 24

    // (2a0+L-1)*L = N*2
    // 2*N/L = (2a0+L-1) => (2*N/L-L+1) = 2a0

    long long ans = 2; // at least N, 1
    long long root = sqrt(N);

    for (long long v = 2; v <= root; ++v) {
        if (N%v == 0) {
            long long v1 = N/v;

            if (checkOK(N, v1)) {
                ++ans;
            }

            if (checkOK(N, v)) {
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}