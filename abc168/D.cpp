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

    VI preV(N, -1);
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

    deque <int> que;
    const int source = 0;
    int reachable = 0;

    que.emplace_back(source);

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();
        ++reachable;

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i];

            if (preV[nextv] == -1 && nextv != source) {
                preV[nextv] = now;
                que.push_back(nextv);
            }
        }
    }

    if (reachable == N) {
        cout << "Yes" << endl;
        for (int i = 1; i < N; ++i) {
            cout << preV[i] + 1 << endl;
        }
    } else {
        cout << "No" << endl;
    }

    return 0;
}