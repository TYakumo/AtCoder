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
    // N * N
    const int INF = 1000000;
    int N;
    cin >> N;

    VLL dp(N+1);
    VLL price(N+1);

    dp[0] = 1000;
    price[0] = INF;

    for (int d = 1; d <= N; ++d) {
        cin >> price[d];
        for (int pd = 0; pd < d; ++pd) {
            // no trading
            dp[d] = max(dp[d], dp[pd]);

            // last trading day
            long long minP = INF;

            for (int i = pd; i < d; ++i) {
                minP = min(minP, price[i]);
            }

            long long allIn = dp[pd] / minP;
            long long remainder = dp[pd] % minP;

            dp[d] = max(dp[d], allIn * price[d] + remainder);
        }
    }

    cout << dp[N] << endl;

    return 0;
}