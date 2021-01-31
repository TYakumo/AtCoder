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
using DI = deque <int>;
const int INF = 1000000000;
const int UNUSED = INF+1;

int solve(const VVI& adja, int f, int t) {
    int N = adja.size();
    VI dist(N, INF);
    DI que;
    dist[f] = 0;
    que.push_back(f);

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();

        for  (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i];

            if (dist[nextv] == INF) {
                dist[nextv] = dist[now]+1;
                que.push_back(nextv);
            }
        }
    }

    return dist[t];
}

int solveDP(const VVI& CD, VVI& DP, int now, int st) {
    int &ret = DP[now][st];
    int K = CD.size();
    int tot = 1<<K;

    if (st == tot-1) {
        return ret = 0;
    }

    if (ret != UNUSED) {
        return ret;
    }

    ret = INF;

    for (int i = 0; i < K; ++i) {
        int nextv = 1<<i;

        if ((nextv&st) == 0 && CD[now][i] != INF) {
            ret = min(ret, CD[now][i] + solveDP(CD, DP, i, st|nextv));
        }
    }

    return ret;
}

int main() {
    int N;
    int M;

    cin >> N >> M;

    VI A(M);
    VI B(M);
    VVI adja(N);
    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i];
        --A[i];
        --B[i];
        adja[A[i]].push_back(B[i]);
        adja[B[i]].push_back(A[i]);
    }

    int K;
    cin >> K;
    VI C(K);

    for (int i = 0; i < K; ++i) {
        cin >> C[i];
        --C[i];
    }

    VVI CD(K, VI(K, INF));

    for (int i = 0; i < K; ++i) {
        CD[i][i] = 0;
        for (int j = i+1; j < K; ++j) {
            CD[i][j] = CD[j][i] = solve(adja, C[i], C[j]);
        }
    }

    int tot = 1<<K;
    int ans = INF;
    VVI DP(K, VI(tot, UNUSED));

    for (int i = 0; i < K; ++i) {
        solveDP(CD, DP, i, 1<<i);
    }

    for (int i = 0; i < K; ++i) {
        ans = min(ans, 1+DP[i][1<<i]);
    }


    if (ans >= INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}