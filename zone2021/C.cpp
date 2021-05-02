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

    VVI cand(N, VI(5));

    int low = 1;
    int up = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> cand[i][j];
            up = max(up, cand[i][j]);
        }
    }

    // N * 2^5 * 3 * log v
    int ans = 0;
    while (low <= up) {
        int mid = (low+up) / 2;
        const int UPPER = 1<<5;
        VI mask(N);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (cand[i][j] >= mid) {
                    mask[i] |= 1<<j;
                }
            }
        }

        VVVI dp(N+1, VVI(UPPER, VI(4)));
        dp[0][0][0] = 1;

        for (int n = 1; n <= N; ++n) {
            for (int s = 0; s < UPPER; ++s) {
                for (int i = 0; i <= 3; ++i) {
                    if (dp[n-1][s][i]) {
                        // not chosen
                        dp[n][s][i] |= dp[n-1][s][i];

                        if (i+1 <= 3) {
                            int news = s | mask[n-1];
                            dp[n][news][i+1] |= dp[n-1][s][i];
                        }
                    }
                }
            }
        }

        if (dp[N][UPPER-1][3]) {
            low = mid+1;
            ans = mid;
        } else {
            up = mid-1;
        }
    }

    cout << ans << endl;

    return 0;
}