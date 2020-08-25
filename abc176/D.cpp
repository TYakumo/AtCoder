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

struct Que {
    Que(int pr, int pc, int pd) : r(pr), c(pc), d(pd) {
    }
    int r;
    int c;
    int d;

    bool operator<(const Que& q) const {
        return d > q.d; // min queue
    }
};

int main() {
    int H;
    int W;
    cin >> H >> W;

    vector <int> C(2);
    vector <int> D(2);
    vector <string> S(H);

    cin >> C[0] >> C[1];
    cin >> D[0] >> D[1];

    --C[0];
    --C[1];
    --D[0];
    --D[1];

    for (int i = 0; i < H; ++i) {
        cin >> S[i];
    }

    VVI best(H, VI(W, -1));
    const char OBSTACLE = '#';

    priority_queue <Que> que;

    if (S[C[0]][C[1]] != OBSTACLE) {
        best[C[0]][C[1]] = 0;
        que.push(Que(C[0], C[1], 0));
    }

    while (!que.empty()) {
        Que q = que.top();
        que.pop();

        // normal
        const int dr[] = {1, -1, 0, 0};
        const int dc[] = {0, 0, 1, -1};

        for (int dir = 0; dir < 4; ++dir) {
            int newr = dr[dir] + q.r;
            int newc = dc[dir] + q.c;

            int newcost = best[q.r][q.c];

            if (newr < H && newr >= 0
            && newc < W && newc >= 0
            && S[newr][newc] != OBSTACLE
            && (best[newr][newc] == -1 || newcost < best[newr][newc])) {
                best[newr][newc] = newcost;
                que.push(Que(newr, newc, newcost));
            }
        }

        // magic
        for (int mdr = -2; mdr <= 2; ++mdr) {
            for (int mdc = -2; mdc <= 2; ++mdc) {
                int newr = mdr + q.r;
                int newc = mdc + q.c;

                int newcost = best[q.r][q.c] + 1;

                if (newr < H && newr >= 0
                && newc < W && newc >= 0
                && S[newr][newc] != OBSTACLE
                && (best[newr][newc] == -1 || newcost < best[newr][newc])) {
                    best[newr][newc] = newcost;
                    que.push(Que(newr, newc, newcost));
                }
            }
        }
    }

    cout << best[D[0]][D[1]] << endl;

    return 0;
}