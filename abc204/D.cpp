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
    int N;
    cin >> N;

    VI T(N);
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
        sum += T[i];
    }

    const int INF = 100000000;
    VVI dp(N+1, VI(sum+1, INF));

    int nows = 0;
    dp[0][0] = 0;

    for (int i = 0; i < N; ++i) {
        for (int t = 0; t <= nows; ++t) {
            dp[i+1][t] = min(dp[i+1][t], dp[i][t]+T[i]);
            dp[i+1][t+T[i]] = min(dp[i+1][t+T[i]], dp[i][t]);
        }
        nows += T[i];
    }

    int ans = INF;
    for (int t = 0; t <= sum; ++t) {
        int res = max(dp[N][t], t);
        ans = min(ans, res);
    }

    cout << ans << endl;



    return 0;
}