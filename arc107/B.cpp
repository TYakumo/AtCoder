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

int main() {
    int N;
    int K;

    cin >> N >> K;
    K = abs(K);

    int UPPER = 2*N;
    VLL comb(UPPER);

    for (int v = 2; v <= UPPER; ++v) {
        // (x, y), x+y = v
        if (v <= N) {
            comb[v] = v-1;
        } else {
            // a+b = v
            // b <= N
            // => a = v-b, a >= v-N, from v-N to N => 2N-v+1
            comb[v] = 2*N-v+1;
        }
    }

    long long ans = 0;

    // a+b-K = c+d
    for (int v = max(2, 2+K); v <= UPPER; ++v) {
        int target = v-K;
        ans += comb[v] * comb[target];
    }

    cout << ans << endl;

    return 0;
}