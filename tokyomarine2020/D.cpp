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
using VVPI = vector <VPI>;
using VMII = vector <map<int, int>>;

const int MAXH = 10;

inline int getHeight(int now) {
    int ret = 0;

    while (now >= 1) {
        now >>= 1;
        ++ret;
    }

    return ret;
}

void solveDP(VMII& dp, int now, int sum, int val, const VI& V, const VI& W, const VI& H) {
    int N = V.size()-1;

    dp[now][sum] = max(dp[now][sum], val);
    dp[now][(sum + W[now])] = max(dp[now][(sum + W[now])], val + V[now]);

    if (H[now] >= MAXH) {
        return ;
    }

    if (now*2 <= N) {
        solveDP(dp, now*2, sum+W[now], val+V[now], V, W, H);
        solveDP(dp, now*2, sum, val, V, W, H);
    }

    if (now*2+1 <= N) {
        solveDP(dp, now*2+1, sum+W[now], val+V[now], V, W, H);
        solveDP(dp, now*2+1, sum, val, V, W, H);
    }
}

int main() {
    int N;
    cin >> N;

    VI V(N+1);
    VI W(N+1);
    VI H(N+1);

    for (int i = 1; i <= N; ++i) {
        H[i] = getHeight(i);
    }

    for (int i = 1; i <= N; ++i) {
        cin >> V[i] >> W[i];
    }

    VMII dp(N+1);
    VVPI vdp(N+1);

    // table creation => O(N) * 2^MAXH
    solveDP(dp, 1, 0, 0, V, W, H);

    // stay monotone
    for (int i = 1; i <= N; ++i) {
        if (!dp[i].empty()) {
            auto iter = dp[i].begin();

            while (iter != dp[i].end()) {
                if (vdp[i].empty() || iter->second > vdp[i].back().second) {
                    vdp[i].push_back(make_pair(-iter->first, iter->second));
                }

                ++iter;
            }

            reverse(vdp[i].begin(), vdp[i].end());
        }
    }

    int Q;
    cin >> Q;

    // Q * 2^(LEVEL-MAXH) * (dp Query => log Comb = MAXH)
    // Q * 2^(LEVEL-MAXH) * MAXH
    while (Q--) {
        int v;
        int L;

        cin >> v >> L;

        if (H[v] <= MAXH) {
            auto iter = lower_bound(vdp[v].begin(), vdp[v].end(), make_pair(-L, 0));
            cout << iter->second << endl;
        } else {
            VI cand;
            int p = v;

            while (H[p] > MAXH) {
                cand.push_back(p);
                p /= 2;
            }

            int allMask = 1<<cand.size();
            int ans = -1;

            // 2^9 * 18
            for (int cho = 0; cho < allMask; ++cho) {
                int sum = 0;
                int val = 0;

                for (int i = 0; i < cand.size(); ++i) {
                    int nowv = cand[i];
                    if (cho & (1<<i)) {
                        sum += W[nowv];
                        val += V[nowv];
                    }
                }

                if (sum <= L) {
                    auto iter = lower_bound(vdp[p].begin(), vdp[p].end(), make_pair(-(L-sum), 0));
                    if (iter != vdp[p].end()) {
                        ans = max(ans, val + iter->second);
                    }
                }
            }

            cout << ans << endl;
        }
    }

    return 0;
}