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

using VI = vector <int>;
using VVI = vector <VI>;
using VPI = vector <pair<int, int>>;

int main() {
    int N;
    int M;
    int Q;

    cin >> N >> M >> Q;

    VPI cand(N);
    VPI X(M);

    for (int i = 0; i < N; ++i) {
        // cin >> W[i] >> V[i];
        cin >> cand[i].first >> cand[i].second;
    }

    sort(cand.begin(), cand.end());

    for (int i = 0; i < M; ++i) {
        cin >> X[i].first;
        X[i].second = i;
    }

    sort(X.begin(), X.end());

    // N*M*Q
    for (int q = 0; q < Q; ++q) {
        int L;
        int R;
        cin >> L >> R;
        --L;
        --R;

        VVI dp(N+1, VI(M+1));

        for (int i = 0; i < N; ++i) {
            dp[i+1] = dp[i];

            int maxVal = 0;
            for (int j = 0; j < M; ++j) {
                maxVal = max(maxVal, dp[i][j]);

                if ((X[j].second < L || X[j].second > R) && X[j].first >= cand[i].first) {
                    dp[i+1][j+1] = max(dp[i+1][j+1], maxVal+cand[i].second);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= M; ++i) {
            ans = max(ans, dp[N][i]);
        }
        cout << ans << endl;
    }


    return 0;
}