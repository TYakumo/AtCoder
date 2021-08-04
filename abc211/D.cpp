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

const long long MOD = 1000000000+7;

struct Que {
    int now;
    int dist;

    Que(int pn, int pd) : now(pn), dist(pd) {}

    bool operator<(const Que& q) const {
        return dist > q.dist;
    }
};

int main() {
    int N;
    int M;
    cin >> N >> M;

    VVI adja(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;
        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    priority_queue <Que> que;
    const int INF = 100000000;
    VLL dp(N);
    VI dist(N, INF);
    VI used(N);
    dp[0] = 1;
    dist[0] = 0;

    que.push(Que(0, 0));

    while (!que.empty()) {
        int now = que.top().now;
        que.pop();

        if (used[now]) {
            continue;
        }

        used[now] = 1;

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i];
            int newdist = dist[now]+1;

            if (newdist < dist[nextv]) {
                dp[nextv] = dp[now];
                dist[nextv] = newdist;
                que.push(Que(nextv, newdist));
            } else if (newdist == dist[nextv]) {
                dp[nextv] += dp[now];
                dp[nextv] %= MOD;
            }
        }
    }

    cout << dp[N-1] << endl;

    return 0;
}