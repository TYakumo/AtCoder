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

struct Que {
    int r;
    int c;
    int d;
    int sp;
    Que () {}
    Que (int pr, int pc, int psp, int pd) : r(pr), c(pc), d(pd), sp(psp) {}

    bool operator<(const Que& q) const {
        return d > q.d;
    }
};

int main() {
    int R;
    int C;
    cin >> R >> C;

    VVI A(R, VI(C));
    VVI B(R, VI(C));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C-1; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < R-1; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> B[i][j];
        }
    }

    const int INF = 1000000000;
    VVVI dp(R, VVI(C, VI(2, INF)));
    priority_queue <Que> pq;
    dp[0][0][1] = 0;
    pq.push(Que(0, 0, 1, 0));

    while (!pq.empty()) {
        Que now = pq.top();
        pq.pop();

        int nr = now.r;
        int nc = now.c;
        int sp = now.sp;
        int newr = 0;
        int newc = 0;
        if (now.d > dp[nr][nc][sp]) {
            continue;
        }

        // left
        if (nc-1 >= 0) {
            newr = nr;
            newc = nc-1;
            int cost = dp[nr][nc][sp] + A[nr][nc-1];

            if (cost < dp[newr][newc][1]) {
                dp[newr][newc][1] = cost;
                pq.push(Que(newr, newc, 1, dp[newr][newc][1]));
            }
        }

        // right
        if (nc+1 < C) {
            newr = nr;
            newc = nc+1;
            int cost = dp[nr][nc][sp] + A[nr][nc];

            if (cost < dp[newr][newc][1]) {
                dp[newr][newc][1] = cost;
                pq.push(Que(newr, newc, 1, dp[newr][newc][1]));
            }
        }

        // down
        if (nr+1 < R) {
            newr = nr+1;
            newc = nc;
            int cost = dp[nr][nc][sp] + B[nr][nc];

            if (cost < dp[newr][newc][1]) {
                dp[newr][newc][1] = cost;
                pq.push(Que(newr, newc, 1, dp[newr][newc][1]));
            }
        }

        // back
        if (nr-1 >= 0) {
            newr = nr-1;
            newc = nc;
            int cost = dp[nr][nc][sp] + (sp+1);

            if (cost < dp[newr][newc][0]) {
                dp[newr][newc][0] = cost;
                pq.push(Que(newr, newc, 0, dp[newr][newc][0]));
            }
        }
    }

    cout << dp[R-1][C-1][1] << endl;

    return 0;
}