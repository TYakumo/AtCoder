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
using VS = vector <string>;

struct Que {
    int r;
    int c;
    int d;

    Que (int pr, int pc, int pd) : r(pr), c(pc), d(pd) {}
    bool operator<(const Que& q) const {
        return d > q.d;
    }
};

int main() {
    int H;
    int W;
    cin >> H >> W;
    VS graph(H);
    for (int i = 0; i < H; ++i) {
        cin >> graph[i];
    }

    const int INF = 100000000;
    VVI dp(H, VI(W, INF));
    VVI used(H, VI(W));
    priority_queue <Que> pque;
    int ans = INF;
    dp[0][0] = 0;
    pque.push(Que(0, 0, 0));

    while (!pque.empty()) {
        Que q = pque.top();
        pque.pop();

        if (q.r == H-1 && q.c == W-1) {
            ans = min(ans, dp[H-1][W-1]);
        }

        if (used[q.r][q.c]) {
            continue;
        }
        used[q.r][q.c] = 1;

        const int dr[] = {1, -1, 0, 0};
        const int dc[] = {0, 0, 1, -1};
        for (int dir = 0; dir < 4; ++dir) {
            int newr = q.r + dr[dir];
            int newc = q.c + dc[dir];

            // two possibility
            if (newr < H && newr >= 0
            && newc < W && newc >= 0
            && used[newr][newc] == 0
            ) {
                if (graph[newr][newc] == '#') {
                    int newcost = dp[q.r][q.c] + 1;
                    if (newcost < dp[newr][newc]) {
                        dp[newr][newc] = newcost;
                        pque.push(Que(newr, newc, newcost));
                    }

                    const int ddr[] = {1, -1, 0, 0, 1, -1, 1, -1};
                    const int ddc[] = {0, 0, 1, -1, 1, -1, -1, 1};
                    for (int tmpd = 0; tmpd < 8; ++ tmpd) {
                        int nnewr = newr + ddr[tmpd];
                        int nnewc = newc + ddc[tmpd];

                        if (nnewr < H && nnewr >= 0
                            && nnewc < W && nnewc >= 0
                            && newcost < dp[nnewr][nnewc]) {
                                dp[nnewr][nnewc] = newcost;
                                pque.push(Que(nnewr, nnewc, newcost));
                            }
                    }
                } else {
                    if (dp[q.r][q.c] < dp[newr][newc]) {
                        dp[newr][newc] = dp[q.r][q.c];
                        pque.push(Que(newr, newc, dp[q.r][q.c]));
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}