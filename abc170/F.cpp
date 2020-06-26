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
using VVVI = vector <VVI>;

struct QueNode {
    int qx;
    int qy;
    int dist;
    int dir;

    QueNode(int px, int py,  int pdir, int pdist) : qx(px), qy(py), dist(pdist), dir(pdir) {
    }

    bool operator<(const QueNode& q) const {
        return dist > q.dist;
    }
};

int main() {
    int H;
    int W;
    int K;

    cin >> H >> W >> K;

    vector <string> pond(H);
    VVVI dp(H, VVI(W, VI(4, -1)));

    VI x(2);
    VI y(2);
    for (int i = 0; i < 2; ++i) {
        cin >> x[i] >> y[i];
        --x[i];
        --y[i];
    }

    for (int i = 0; i < H; ++i) {
        cin >> pond[i];
    }

    priority_queue <QueNode> que;
    dp[x[0]][y[0]][0] = 0;
    que.push(QueNode(x[0], y[0], 0, 0));

    while (!que.empty()) {
        int qx = que.top().qx;
        int qy = que.top().qy;
        int qdir = que.top().dir;
        int qdist = que.top().dist;

        que.pop();

        if (qdist > dp[qx][qy][qdir]) {
            continue;
        }

        if (qx == x[1] && qy == y[1]) {
            break;
        }

        const int dx[] = {1, -1, 0, 0};
        const int dy[] = {0, 0, 1, -1};

        for (int dir = 0; dir < 4; ++dir) {
            int nqx = qx + dx[dir];
            int nqy = qy + dy[dir];
            int nd = (dir == qdir) ? dp[qx][qy][qdir] + 1 : (((dp[qx][qy][qdir]+K-1)/K)*K) + 1;

            if (nqx >= 0 && nqx < H
                && nqy >= 0 && nqy < W) {
                if (pond[nqx][nqy] != '@' && (dp[nqx][nqy][dir] == -1 || nd < dp[nqx][nqy][dir])) {
                    dp[nqx][nqy][dir] = nd;
                    que.push(QueNode(nqx, nqy, dir, nd));
                }
            }
        }
    }

    const int MAXVAL = 1000000010;
    int ans = MAXVAL;

    for (int dir = 0; dir < 4; ++dir) {
        if (dp[x[1]][y[1]][dir] > 0) {
            ans = min(ans, dp[x[1]][y[1]][dir]);
        }
    }

    cout << (ans == MAXVAL ? -1 : (ans+K-1)/K) << endl;

    return 0;
}