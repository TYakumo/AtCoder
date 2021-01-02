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
#include <deque>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    VVI adja(N, VI(N));
    for (int i = 0; i < M; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --a;
        --b;
        adja[b][a] = adja[a][b] = 1;
    }

    int STATE = 1<<N;
    const int INF = 1000000;
    VI cs;

    for (int st = 1; st < STATE; ++st) {
        bool clique = true;
        for (int i = 0; i < N && clique; ++i) {
            int is = 1<<i;
            if (is & st) {
                for (int j = 0; j < N; ++j) {
                    int js = 1<<j;

                    if (js & st) {
                        if (i != j && adja[i][j] == 0) {
                            clique = false;
                            break;
                        }
                    }
                }
            }
        }

        if (clique) {
            cs.push_back(st);
        }
    }

    VI dp(STATE, INF);
    dp[0] = 0;
    deque <pair<int, int>> que;
    que.push_back({0, 0});
    sort(cs.begin(), cs.end(), greater<int>());
    int N2 = (N+1)/2;

    while (!que.empty()) {
        int now = que.front().first;
        int start = que.front().second;
        que.pop_front();

        if (dp[now] >= N2) {
            break;
        }

        for (int i = start; i < cs.size(); ++i) {
            if ((cs[i] & now) == 0) {
                int nexts = cs[i] | now;
                if (dp[nexts] == INF) {
                    dp[nexts] = dp[now]+1;
                    que.push_back({nexts, i+1});

                    if (nexts == STATE-1) {
                        break;
                    }
                }
            }
        }
    }

    if (dp[STATE-1] == INF) {
        for (int s = 1; s < STATE; ++s) {
            int comple = (STATE-1) ^ s;
            dp[STATE-1] = min(dp[STATE-1], dp[comple] + dp[s]);
        }
    }

    cout << dp[STATE-1] << endl;

    return 0;
}