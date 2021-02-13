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
using VLL = vector <long long>;

struct que {
    int now;
    long long W;
    que () {
    }

    que (int pn, long long pw) : now(pn), W(pw) {
    }

    bool operator<(const que& a) const {
        return W > a.W;
    }
};

int main() {
    int N;
    int M;

    cin >> N >> M;

    const long long INF = 1000000000000000LL;
    VVI adja(N);
    VVI W(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        int c;
        cin >> f >> t >> c;
        --f;
        --t;
        adja[f].push_back(t);
        W[f].push_back(c);
    }

    for (int i = 0; i < N; ++i) {
        VLL dp(N+1, INF);
        priority_queue <que> pq;
        VI used(N);

        dp[i] = 0;
        pq.push(que(i, 0));

        while (!pq.empty()) {
            int now = pq.top().now;
            pq.pop();

            if (now == N || used[now]) {
                continue;
            }

            used[now] = 1;

            for (int j = 0; j < adja[now].size(); ++j) {
                int nextv = adja[now][j] == i ? N : adja[now][j];
                int weight = W[now][j];
                long long newWeight = weight + dp[now];

                if (newWeight < dp[nextv]) {
                    dp[nextv] = newWeight;
                    pq.push(que(nextv, newWeight));
                }
            }
        }

        if (dp[N] == INF) {
            cout << -1 << endl;
        } else {
            cout << dp[N] << endl;
        }
    }




    return 0;
}