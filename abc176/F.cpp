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
using VVVI = vector <VVI>;

int main() {
    int N;
    cin >> N;

    // iteration, number, num
    VI A(3*N);

    for (int i = 0; i < 3*N; ++i) {
        cin >> A[i];
    }

    VVVI dp(N+1, VVI(3, VI(N+1, -1)));

    dp[0][0][0] = 0;

    for (int it = 0; it < N; ++it) {
        for (int n = 0; n < 3; ++n) {
            for (int num = 0; num <= N; ++num) {
                if (dp[it][n][num] == -1) {
                    continue;
                }

                int plus = 0;
                // starting from [it*3, it*3+5]
                unordered_map <int, int> counter;
                if (it == 0) {
                    for (int r = 0; r < 5 && r < 3*N; ++r) {
                        ++counter[A[r]];
                    }
                } else {
                    if (num) {
                        counter[num] += n;
                    }

                    int offset = it*3 + 2;
                    for (int r = 0; r < 3 && r + offset < 3*N; ++r) {
                        ++counter[A[offset + r]];
                    }
                }

                auto iter = counter.begin();
                while (iter != counter.end()) {
                    if (iter->second >= 3) {
                        iter->second -= 3;
                        plus = 1;
                        break;
                    }
                    ++iter;
                }

                // choose remain
                iter = counter.begin();
                while (iter != counter.end()) {
                    dp[it+1][min(2, iter->second)][iter->first] = max(dp[it+1][min(2, iter->second)][iter->first], dp[it][n][num]+plus);
                    ++iter;
                }

                // reserve no number
                // dp[it+1][0][0] = max(dp[it+1][0][0], dp[it][n][num]+plus);
            }
        }
    }

    int ans = 0;

    for (int n = 0; n < 3; ++n) {
        for (int v = 0; v <= N; ++v) {
            ans = max(ans, dp[N][n][v]);
        }
    }

    cout << ans << endl;

    return 0;
}