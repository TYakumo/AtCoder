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

using VS = vector <string>;
using VI = vector <int>;
using VVI = vector <VI>;
using US = unordered_set<int>;
using VUS = vector <US>;

int solve(VS graph) {
    int R = graph.size();
    int C = graph[0].size();
    int ans = R-2;

    VUS gp(C);
    US covered;
    US cand;

    graph[0][C-1] = graph[R-1][C-1] = graph[0][0] = graph[R-1][0] = '#';

    for (int i = 0; i < R; ++i) {
        cand.insert(i);
        for (int j = 0; j < C; ++j) {
            if (graph[i][j] == '#') {
                gp[j].insert(i);
            }
        }
    }

    deque <int> que;
    que.push_back(0);
    que.push_back(R-1);
    cand.erase(cand.find(0));
    cand.erase(cand.find(R-1));

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();

        for (int c = 0; c < C; ++c) {
            if (graph[now][c] == '#' && covered.find(c) == covered.end()) {
                covered.insert(c);

                auto iter = gp[c].begin();
                while (iter != gp[c].end()) {
                    if (cand.find(*iter) != cand.end()) {
                        que.push_back(*iter);
                        cand.erase(*iter);
                        --ans;
                    }
                    ++iter;
                }

                gp[c].clear();
            }
        }

        if (cand.size() && que.empty()) {
            que.push_back(*cand.begin());
            cand.erase(cand.begin());
        }
    }

    return ans;
}

VS rotate(const VS& graph) {
    int R = graph.size();
    int C = graph[0].size();
    VS ret(C, string(R, '.'));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            ret[j][i] = graph[i][j];
        }
    }

    return ret;
}

int main() {
    int H;
    int W;
    cin >> H >> W;

    VS graph(H);

    for (int i = 0; i < H; ++i) {
        cin >> graph[i];
    }

    cout << min(solve(graph), solve(rotate(graph))) << endl;

    return 0;
}