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

int main() {
    int N;
    int X;
    int Y;

    cin >> N;
    cin >> X >> Y;
    --X;
    --Y;

    const int INF = 1000000;
    vector< vector<int> > dist(N);
    vector < vector<int> > adja(N);
    vector<int> distCount(N);

    adja[X].push_back(Y);
    adja[Y].push_back(X);

    for (int i = 1; i < N; ++i) {
        adja[i].push_back(i-1);
        adja[i-1].push_back(i);
    }

    for (int i = 0; i < N; ++i) {
        deque <int> que;
        que.push_back(i);
        dist[i] = move(vector<int>(N, INF));
        dist[i][i] = 0;

        while (!que.empty()) {
            int now = que.front();
            que.pop_front();

            for (int j = 0; j < adja[now].size(); ++j) {
                int nextv = adja[now][j];

                if (dist[i][nextv] == INF) {
                    dist[i][nextv] = dist[i][now] + 1;
                    que.push_back(nextv);
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            ++distCount[dist[i][j]];
        }
    }


    for (int i = 1; i < N; ++i) {
        cout << distCount[i] << endl;
    }


    return 0;
}