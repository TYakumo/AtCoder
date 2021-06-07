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
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    VVI adja(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        adja[f-1].push_back(t-1);
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        VI visited(N);
        deque <int> que;
        que.push_back(i);
        visited[i] = 1;

        while (!que.empty()) {
            int now = que.front();
            que.pop_front();
            ++ans;

            for (int i = 0; i < adja[now].size(); ++i) {
                int nextv = adja[now][i];

                if (visited[nextv] == 0) {
                    visited[nextv] = 1;
                    que.push_back(nextv);
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}