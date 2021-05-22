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
#include <random>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;

using VD = vector <double>;
using VVD = vector <VD>;
using VVVD = vector <VVD>;

using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

const int MAXN = 30;
int globalCnt = 0;
const int RND_MAXN = 200000;
VI rndVal(RND_MAXN);

struct Queue {
    int r;
    int c;
    double cost;

    Queue (int pr, int pc, double dcost) : r(pr), c(pc), cost(dcost) {}
    bool operator<(const Queue& q) const {
        return cost > q.cost;
    }
};

inline double processFunc(double v, double avg) {
    // double ratio = v/avg;

    // double base = 70 * ratio;
    // double offset = rndVal[globalCnt];
    // globalCnt = (globalCnt+1)%RND_MAXN;
    // return base + ratio*offset;
    return v;
}

int main() {
    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};
    const char dch[] = {'D', 'U', 'R', 'L'};
    // const int oppDir[] = {1, 0, 3, 2};
    unordered_map <char, int> chToIdx;

    random_device seed_gen;
    mt19937 engine(seed_gen());

    for (int i = 0; i < RND_MAXN; ++i) {
        rndVal[i] = engine()%10;
    }

    for (int i = 0; i < 4; ++i) {
        chToIdx[dch[i]] = i;
    }

    VI p(4);
    const double INIT_VALUE = 5000;
    const double INF = 1e+18;
    const int TIMES = 1000;
    VVVD expected(MAXN, VVD(MAXN, VD(4, INIT_VALUE)));
    VVVI cnt(MAXN, VVI(MAXN, VI(4)));

    for (int t = 0; t < TIMES; ++t) {
        cin >> p[0] >> p[1] >> p[2] >> p[3];
        string ans;
        VVD dp(MAXN, VD(MAXN, INF));
        VVI pre(MAXN, VI(MAXN, -1));
        VVI used(MAXN, VI(MAXN));
        VVVD localExpected = expected;
        priority_queue<Queue> pq;
        dp[p[0]][p[1]] = 0;
        pq.push(Queue(p[0], p[1], 0));

        while (!pq.empty()) {
            Queue now = pq.top();
            int nr = now.r;
            int nc = now.c;
            pq.pop();

            if (used[nr][nc]) {
                continue;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int newr = nr + dr[dir];
                int newc = nc + dc[dir];
                double cost = dp[nr][nc] + expected[nr][nc][dir];

                if (newr >= 0 && newr < MAXN
                && newc >= 0 && newc < MAXN
                && cost < dp[newr][newc]) {
                    dp[newr][newc] = cost;
                    pq.push(Queue(newr, newc, cost));
                    pre[newr][newc] = dir;
                }
            }
        }

        // cerr << "START TRACING" << endl;
        // tracing
        int nr = p[2];
        int nc = p[3];

        while (nr != p[0] || nc != p[1]) {
            int dir = pre[nr][nc];
            // cerr << "NOW " << nr << " " << nc << " " << dir << endl;
            ans += dch[dir];
            nr -= dr[dir];
            nc -= dc[dir];
        }

        // cerr << "END TRACING" << endl;
        reverse(ans.begin(), ans.end());
        cout << ans << endl;

        double cost;
        cin >> cost;

        // update
        nr = p[0];
        nc = p[1];
        double avg = cost / dp[p[2]][p[3]];

        for (int i = 0; i < ans.size(); ++i) {
            int dir = chToIdx[ans[i]];
            double plus = avg * expected[nr][nc][dir];
            ++cnt[nr][nc][dir];
            if (cnt[nr][nc][dir] == 1) {
                expected[nr][nc][dir] = plus;
            } else {
                expected[nr][nc][dir] *= (cnt[nr][nc][dir]-1);
                expected[nr][nc][dir] += plus;
                expected[nr][nc][dir] /= (cnt[nr][nc][dir]);
            }

            nr += dr[dir];
            nc += dc[dir];
        }
    }

    return 0;
}