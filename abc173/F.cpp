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
    long long ans = 0;
    cin >> N;

    // for (int i = 1; i <= N; ++i) {
    //     ans += i * (N-i+1); // sigma (N+1)*i - i^2
    // }

    // (N+1) * N*(N+1) / 2 = 3*(N+1) * (N) * (N+1) / 6
    // - N(N+1)(2N+1) / 6

    // (3N+3 - 2N-1) * N * (N+1)/6
    // (N+2)*N*(N+1)/6
    ans = (N+2)*N*(N+1)/6;

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        cin >> f >> t;
        if (t < f) {
            swap(t, f);
        }
        ans -= f * (N-t+1);
    }

    cout << ans << endl;

    return 0;
}