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
#include <queue>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
const int MAXC = 26;

int main() {
    int N;
    int M;

    cin >> N >> M;

    VVVI adja(N, VVI(MAXC));
    const int INF = 1000000000;
    VVI dp(N, VI(N, INF));
    deque <pair<int, int>> que;

    for (int i = 0; i < N; ++i) {
        que.push_back({i, i});
        dp[i][i] = 0;
    }

    for (int i = 0; i < M; ++i) {
        int a;
        int b;
        char c;
        cin >> a >> b >> c;

        --a;
        --b;
        adja[a][c-'a'].push_back(b);
        adja[b][c-'a'].push_back(a);

        if (dp[a][b] == INF) {
            dp[a][b] = dp[b][a] = 1;
            que.push_back({a, b});
            que.push_back({b, a});
        }
    }


    while (!que.empty()) {
        pair <int, int> nowP = que.front();
        que.pop_front();

        int now = nowP.first;
        int nextv = nowP.second;
        int cost = dp[now][nextv] + 2;

        for (int c = 0; c < MAXC; ++c) {
            for (int a = 0; a < adja[now][c].size(); ++a) {
                for (int b = 0; b < adja[nextv][c].size(); ++b) {
                    int nnow = adja[now][c][a];
                    int nnextv = adja[nextv][c][b];

                    if (cost < dp[nnow][nnextv]) {
                        dp[nnow][nnextv] = cost;
                        que.push_back({nnow, nnextv});
                    }
                }
            }
        }
    }

    cout << (dp[0][N-1] == INF ? -1 : dp[0][N-1]) << endl;

    return 0;
}