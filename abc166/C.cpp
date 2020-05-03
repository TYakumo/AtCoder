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
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

void solve(int now, VI& visit, VI& H, VI& maxNeigh, VVI& adja) {
    visit[now] = 1;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (visit[nextv] == 0) {
            solve(nextv, visit, H, maxNeigh, adja);
        }

        maxNeigh[nextv] = max(maxNeigh[nextv], H[now]);
        maxNeigh[now] = max(maxNeigh[now], H[nextv]);
    }
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    VI H(N);
    VVI adja(N);
    VI visit(N);
    VI maxNeigh(N);

    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;
        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    for (int i = 0; i < N; ++i) {
        if (visit[i] == 0) {
            solve(i, visit, H, maxNeigh, adja);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (maxNeigh[i] < H[i]) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}