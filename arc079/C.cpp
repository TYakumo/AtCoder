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

using VI = vector<int>;
using VVI = vector<VI>;

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
    }

    deque <int> que;
    VI dist(N, -1);
    que.push_back(0);
    dist[0] = 0;

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i];

            if (dist[nextv] == -1 && dist[now] < 2) {
                dist[nextv] = dist[now]+1;
                que.push_back(nextv);
            }
        }
    }

    if (dist[N-1] != -1) {
        cout << "POSSIBLE" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}