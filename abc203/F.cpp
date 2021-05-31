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
    int K;
    cin >> N >> K;

    VI A(N);
    const int INF = 1000000000;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());
    const int MAX_STEPS = 32;

    VVI dp(K+1, VI(MAX_STEPS+1));
    for (int k = 0; k <= K; ++k) {
        dp[k][0] = k;
    }

    for (int k = 0; k <= K; ++k) {
        for (int s = 0; s <= MAX_STEPS; ++s) {
            int now = N-1-dp[k][s];

            // skip
            if (k+1 <= K && dp[k][s] <= N) {
                dp[k+1][s] = max(dp[k+1][s], dp[k][s]+1);
            }

            // choose
            auto iter = upper_bound(A.begin(), A.end(), A[now]/2);
            int idx = (iter-A.begin());
            dp[k][s+1] = max(dp[k][s+1], (N-idx));
        }
    }

    VI ans = {INF, 0};
    for (int k = 0; k <= K; ++k) {
        for (int s = 0; s <= MAX_STEPS; ++s) {
            if (dp[k][s] >= N) {
                VI res = {s, k};

                if (res < ans) {
                    ans = res;
                }
            }
        }
    }

    cout << ans[0] << " " << ans[1] << endl;

    return 0;
}