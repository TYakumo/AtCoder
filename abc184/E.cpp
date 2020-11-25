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
using VI = vector<int>;
using VVI = vector <VI>;
using PII = vector<int>;
using VPII = vector <PII>;
using VVPII = vector <VPII>;
using QPII = deque <PII>;

int main() {
    int H;
    int W;
    cin >> H >> W;

    const int INF = 1000000;
    VS strMap(H);
    VVPII teleport(26);
    VVI dist(H, VI(W, INF));
    VI visited(26);
    QPII que;

    int SR;
    int SC;
    int ER;
    int EC;

    for (int i = 0; i < H; ++i) {
        cin >> strMap[i];

        for (int j = 0; j < strMap[i].size(); ++j) {
            if (strMap[i][j] >= 'a' && strMap[i][j] <= 'z') {
                int chNum = strMap[i][j] - 'a';
                teleport[chNum].push_back({i, j});
            } else if (strMap[i][j] == 'S') {
                SR = i;
                SC = j;
            } else if (strMap[i][j] == 'G') {
                ER = i;
                EC = j;
            }
        }
    }

    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};
    dist[SR][SC] = 0;
    que.push_back({SR, SC});

    while (!que.empty()) {
        PII now = que.front();
        que.pop_front();

        for (int dir = 0; dir < 4; ++dir) {
            int newr = now[0] + dr[dir];
            int newc = now[1] + dc[dir];

            if (newr < H && newr >= 0
            && newc < W && newc >= 0
            && strMap[newr][newc] != '#'
            && dist[newr][newc] == INF) {
                dist[newr][newc] = dist[now[0]][now[1]] + 1;
                que.push_back({newr, newc});
            }
        }

        if (strMap[now[0]][now[1]] >= 'a' && strMap[now[0]][now[1]] <= 'z') {
            int chNum = strMap[now[0]][now[1]] - 'a';
            if (visited[chNum] == 0) {
                visited[chNum] = 1;
                for (int i = 0; i < teleport[chNum].size(); ++i) {
                    int newr = teleport[chNum][i][0];
                    int newc = teleport[chNum][i][1];

                    if (dist[newr][newc] == INF) {
                        dist[newr][newc] = dist[now[0]][now[1]] + 1;
                        que.push_back({newr, newc});
                    }
                }
            }
        }
    }


    cout << (dist[ER][EC] == INF ? -1 : dist[ER][EC]) << endl;

    return 0;
}