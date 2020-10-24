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

void solve(int now, MLL& wmap, VI& used, VI& order, VLL& w, long long& ans) {
    if (now == w.size()) {
        int N = w.size();
        VLL wsum(N);

        wsum[0] = w[order[0]];

        for (int i = 1; i < N; ++i) {
            wsum[i] = wsum[i-1] + w[order[i]];
        }

        VLL dp(N);

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                long long segWeight = i>0 ? wsum[j] - wsum[i-1] : wsum[j];
                auto iter = wmap.lower_bound(segWeight);
                --iter;

                long long leng = iter->second;
                // dist[i] - dist[j] >= leng
                // -leng >= dist[j] - dist[i]
                dp[j] = max(dp[j], dp[i]+leng);
            }
        }

        ans = min(ans, dp[N-1]);

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