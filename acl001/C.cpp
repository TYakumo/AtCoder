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
#include <atcoder/mincostflow>
using namespace std;
using namespace atcoder;

using VS = vector<string>;
using PI = pair<int, int>;
using DPI = deque<PI>;
using VI = vector <int>;
using VVI = vector<VI>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    const int INF = 100000;
    VS str(N);
    VVI dist(N, VI(M, INF));
    VVI idx(N, VI(M));

    int LV = 0;
    int RV = N*M;

    for (int i = 0; i < N; ++i) {
        cin >> str[i];
        for (int j = 0; j < M; ++j) {
            if (str[i][j] == 'o') {
                idx[i][j] = ++LV;
            }
        }
    }

    int SINK = 1+RV+LV;
    int SOURCE = 0;
    mcf_graph<int, int> graph(SINK+2);
    // SINK 0, LV : 1 ... LV, RV: LV+1 .... LV+RV

    for (int i = 1; i <= LV; ++i) {
        graph.add_edge(SOURCE, i, 1, 0);
    }

    for (int i = 1; i <= RV; ++i) {
        graph.add_edge(LV+i, SINK, 1, 0);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (str[i][j] == 'o') {
                dist = move(VVI(N, VI(M, INF)));
                dist[i][j] = 0;
                int vNum = idx[i][j];

                DPI que;
                que.emplace_back(make_pair(i, j));

                while (!que.empty()) {
                    PI now = que.front();
                    que.pop_front();

                    // graph construction
                    int toVNum = LV + (now.first*M + now.second) + 1;
                    graph.add_edge(vNum, toVNum, 1, INF-dist[now.first][now.second]);

                    // BFS
                    const int dr[] = {1, 0};
                    const int dc[] = {0, 1};

                    for (int dir = 0; dir < 2; ++dir) {
                        int newr = now.first + dr[dir];
                        int newc = now.second + dc[dir];

                        if (newr >= 0 && newr < N
                        && newc >= 0 && newc < M
                        && str[newr][newc] != '#'
                        && dist[newr][newc] == INF) {
                            dist[newr][newc] = dist[now.first][now.second] + 1;
                            que.emplace_back(make_pair(newr, newc));
                        }
                    }
                }
            }
        }
    }

    // min cost maxflow
    auto result = graph.flow(SOURCE, SINK);
    cout << (INF*LV - result.second) << endl;

    return 0;
}