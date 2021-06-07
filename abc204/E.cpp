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
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

struct Que {
    int now;
    long long dist;

    Que (int pn, long long pd) : now(pn), dist(pd) {}

    bool operator<(const Que& q) const {
        return dist > q.dist;
    }
};

int main() {
    int N;
    int M;

    cin >> N >> M;
    VVVLL adja(N);

    for (int i = 0; i < M; ++i) {
        int a;
        int b;
        int c;
        int d;
        cin >> a >> b >> c >> d;
        --a;
        --b;

        adja[a].push_back({b, c, d});
        adja[b].push_back({a, c, d});
    }

    const long long INF = 1000000000LL * 100000000LL;
    VLL dp(N, INF);
    VI used(N);
    priority_queue <Que> pq;
    dp[0] = 0;
    pq.push(Que(0, 0));

    while (!pq.empty()) {
        Que tq = pq.top();
        int now = tq.now;
        pq.pop();

        // cout << "DEBUG " << now << " " << dp[now] << endl;

        if (used[now]) {
            continue;
        }

        used[now] = 1;
        long long nt = dp[now];

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i][0];
            long long C = adja[now][i][1];
            long long D = adja[now][i][2];

            // cost = dt + (C + (D/(nt+1+dt)))
            long long low = 0;
            long long up = nt ? D/nt : D;
            auto costCal = [&nt, &C, &D](long long dt) { return nt+dt+(C+D/(nt+1+dt)); };
            long long best = costCal(0);

            // 0 = 1 - D/(nt+1+dt)^2
            // D = (nt+1+dt)^2
            // sqrt(D)-nt-1

            long long base = sqrt(D)-nt-1;
            for (long long vdt = max(0LL, base-10); vdt <= base+10; ++vdt) {
                best = min(best, costCal(vdt));
            }

            if (best < dp[nextv]) {
                dp[nextv] = best;
                pq.push(Que(nextv, best));
            }
        }
    }

    cout << (dp[N-1] == INF ? -1 : dp[N-1]) << endl;

    return 0;
}