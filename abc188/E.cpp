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

int main() {
    int N;
    int M;
    cin >> N >> M;

    const int INF = 2000000000+10;
    VI A(N);
    VVI adja(N);
    VI in(N);
    VI minPrice(N, INF);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        minPrice[i] = A[i];
    }


    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;
        adja[f].push_back(t);
        ++in[t];
    }

    deque <int> que;
    int bestVal = -INF;
    for (int i = 0; i < N; ++i) {
        if (in[i] == 0) {
            que.push_back(i);
        }
    }

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();

        for (int i = 0; i < adja[now].size(); ++i) {
            int nextv = adja[now][i];

            --in[nextv];
            int profit = A[nextv]-minPrice[now];
            minPrice[nextv] = min(minPrice[nextv], minPrice[now]);
            bestVal = max(bestVal, profit);

            if (in[nextv] == 0) {
                que.push_back(nextv);
            }
        }
    }

    cout << bestVal << endl;

    return 0;
}