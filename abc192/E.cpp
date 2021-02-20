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
using VLL = vector <long long>;

struct que {
    int now;
    long long dist;

    que(int n, long long d) : now(n), dist(d) {
    }

    que() {
    }

    bool operator<(const que& q) const {
        if (dist != q.dist) {
            return dist > q.dist;
        }

        return now < q.now;
    }
};

int main() {
    int N;
    int M;
    int X;
    int Y;
    cin >> N >> M >> X >> Y;

    const long long INF = 1000000000LL * 1000000000LL;
    VVVI adja(N);
    VLL dist(N, INF);

    for (int i = 0; i < M; ++i) {
        VI vec;
        int a;
        int b;
        int t;
        int k;

        cin >> a >> b >> t >> k;
        --a;
        --b;

        vec.push_back(b);
        vec.push_back(t);
        vec.push_back(k);
        adja[a].push_back(vec);

        vec[0] = a;
        adja[b].push_back(vec);
    }

    --X;
    --Y;
    dist[X] = 0;
    priority_queue <que> pq;
    pq.push(que(X, 0));

    while (!pq.empty()) {
        int now = pq.top().now;
        pq.pop();

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i][0];
            long long K = adja[now][i][2];
            long long edgecost = (K-dist[now]%K)%K;
            long long newcost = dist[now]+adja[now][i][1]+edgecost;

            if (newcost < dist[nextv]) {
                dist[nextv] = newcost;
                pq.push(que(nextv, newcost));
            }
        }
    }

    cout << (dist[Y] == INF ? -1 : dist[Y]) << endl;

    return 0;
}