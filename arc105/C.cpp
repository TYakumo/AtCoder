#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cmath>
using namespace std;

using VI = vector <int>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using MLL = map <long long, long long>;

const long long INF = 1000000000000000LL;

template <typename T>
struct Edge {
    int to;
    T w;

    Edge() {}
    Edge(int pt, T pw) : to(pt), w(pw) { }
};

template <typename T>
class SPFA {
    using VE = vector<Edge<T>>;
    using VVE = vector<VE>;
    using VI = vector <int>;
    using VT = vector <T>;
    // const T INF = 1000000000;

    int V;
    VI prev;
    VVE adja;
    VT dist;

public:
    SPFA(int PV) {
        V = PV;
        adja = VVE(V);
        prev = VI(V, -1);
        dist = VT(V, INF);
    }

    bool sssp(int src) {
        deque <int> que;
        VI inQue(V);
        VI prevTime(V);

        dist[src] = 0;
        inQue[src] = 1;
        que.push_back(src);

        while (!que.empty()) {
            int now = que.front();
            que.pop_front();

            inQue[now] = 0;

            for (int i = 0; i < adja[now].size(); ++i) {
                int nextv = adja[now][i].to;
                T newdist = dist[now] + adja[now][i].w;

                if (newdist < dist[nextv]) {
                    dist[nextv] = newdist;
                    prev[nextv] = now;
                    prevTime[nextv] = prevTime[now] + 1;

                    if (prevTime[nextv] == V) {
                        return true; // negative cycle
                    }

                    if (inQue[nextv] == 0) {

                        if (que.empty() || dist[nextv] >= dist[que.front()]) {
                            que.push_back(nextv);
                        } else {
                            que.push_front(nextv);
                        }

                        inQue[nextv] = 1;
                    }
                }
            }
        }

        return false;
    }

    T getBest(int v) {
        return dist[v];
    }

    void addEdge(int f, int t, T w) {
        adja[f].emplace_back(Edge(t, w));
    }

    vector <int> findPath(int src, int dest) {
        vector <int> ret;
        int now = dest;

        while (now != -1) {
            ret.push_back(now);
            now = prev[now];
        }

        if (!ret.empty() && ret.back() != src) { // src can't connect to dest
            ret.clear();
        } else {
            reverse(ret.begin(), ret.end());
        }

        return ret;
    }
};

void solve(int now, MLL& wmap, VI& used, VI& order, VLL& w, long long& ans) {
    if (now == w.size()) {
        int N = w.size();
        VLL wsum(N);

        wsum[0] = w[order[0]];

        for (int i = 1; i < N; ++i) {
            wsum[i] = wsum[i-1] + w[order[i]];
        }

        SPFA<long long> g(N);
        VLL dp(N);

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                long long segWeight = i>0 ? wsum[j] - wsum[i-1] : wsum[j];
                auto iter = wmap.lower_bound(segWeight);
                --iter;

                long long leng = iter->second;
                // dist[i] - dist[j] >= leng
                // -leng >= dist[j] - dist[i]
                g.addEdge(i, j, -leng);
                // dp[j] = max(dp[j], dp[i]+leng);
            }
        }

        if (!g.sssp(0)) { // no negative cycle
            long long res = g.getBest(N-1) - g.getBest(0);
            ans = min(ans, -res);
        }

        // ans = min(ans, dp[N-1]);

        return ;
    }

    for (int i = 0; i < used.size(); ++i) {
        if (used[i] == 0) {
            used[i] = 1;
            order[now] = i;
            solve(now+1, wmap, used, order, w, ans);
            used[i] = 0;
        }
    }
}

int main() {
    int N;
    int M;
    long long ans = INF;

    cin >> N >> M;

    VLL w(N);
    long long maxw = 0;

    for (int i = 0; i < N; ++i) {
        cin >> w[i];
        maxw = max(maxw, w[i]);
    }

    VVLL lv;
    long long minv = INF;

    for (int i = 0; i < M; ++i) {
        long long l;
        long long v;
        cin >> l >> v;

        minv = min(minv, v);
        lv.push_back({v, l});
    }

    MLL wmap;
    sort(lv.begin(), lv.end());
    wmap[0] = 0;
    wmap[INF] = INF;

    // (v, l), monotone increasing, v+ => l+
    for (int i = 0; i < lv.size(); ++i) {
        if (i+1 == lv.size() || lv[i][0] != lv[i+1][0]) {
            wmap[lv[i][0]] = lv[i][1];
        }
    }

    auto iter = wmap.begin();
    auto preIter = iter;

    while (iter != wmap.end()) {
        iter->second = max(iter->second, preIter->second);
        preIter = iter;
        ++iter;
    }

    VI used(N);
    VI order(N);

    if (minv >= maxw) {
        solve(0, wmap, used, order, w, ans);
    }

    cout << (ans == INF ? -1 : ans) << endl;

    return 0;
}