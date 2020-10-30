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

using VLL = vector <long long>;
using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int N;
    cin >> N;

    VVI adja(N);
    VI vcnt(N);
    VLL c(N);
    VLL num(N, -1);

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        cin >> f >> t;

        --f;
        --t;

        adja[f].push_back(t);
        adja[t].push_back(f);
        ++vcnt[t];
        ++vcnt[f];
    }

    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }

    sort(c.begin(), c.end());
    deque<int> que;

    for (int i = 0; i < N; ++i) {
        if (vcnt[i] <= 1) {
            que.push_back(i);
        }
    }

    long long ans = 0;

    for (int i = 0; i < c.size(); ++i) {
        int now = que.front();
        que.pop_front();

        num[now] = c[i];

        for (int j = 0; j < adja[now].size(); ++j) {
            int nextv = adja[now][j];

            if (num[nextv] == -1) {
                --vcnt[nextv];
                if (vcnt[nextv] <= 1) {
                    que.push_back(nextv);
                }
            } else {
                long long minv = num[nextv];
                ans += minv;
            }
        }
    }

    cout << ans << endl;
    for (int i = 0; i < N; ++i) {
        if (i) {
            cout << " ";
        }
        cout << num[i];
    }
    cout << endl;

    return 0;
}