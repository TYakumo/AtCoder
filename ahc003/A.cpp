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

int main() {
    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};
    const char dch[] = {'D', 'U', 'R', 'L'};
    const int oppDir[] = {1, 0, 3, 2};
    unordered_map <char, int> chToIdx;

    for (int i = 0; i < 4; ++i) {
        chToIdx[dch[i]] = i;
    }

    VI p(4);
    const double FACTOR = 1.2;
    // const double INIT_VALUE = 5000/FACTOR;
    const double INIT_VALUE = 5000;
    const double INF = 1e+18;
    const int TIMES = 1000;
    const double R = 0.45;
    VVVD expected(MAXN, VVD(MAXN, VD(4, INIT_VALUE)));
    VVVI cnt(MAXN, VVI(MAXN, VI(4)));
    double costAvg = INIT_VALUE;

    random_device seed_gen;
    mt19937 engine(seed_gen());

    for (int i = 0; i < RND_MAXN; ++i) {
        rndVal[i] = engine()%300;
    }

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

        int tmp = engine()%rndVal.size();

        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                for (int dir = 0; dir < 4; ++dir) {
                    if (cnt[i][j][dir] == 0) {
                        localExpected[i][j][dir] += rndVal[tmp];
                    }
                    tmp = (tmp+1) % rndVal.size();
                }
            }
        }

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
                // double cost = dp[nr][nc] + localExpected[nr][nc][dir];

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
        costAvg = costAvg*R + cost*(1.0-R);
        // if (cost/costAvg < 0.7) {
        //     cost /= 0.9;
        // }
        // if (cost/costAvg > 1.3) {
        //     cost /= 1.1;
        // }
        cost *= FACTOR;

        // update
        nr = p[0];
        nc = p[1];
        double distSum = 0;

        for (int i = 0; i < ans.size(); ++i) {
            int dir = chToIdx[ans[i]];

            double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
            distSum += scalingFactor;

            nr += dr[dir];
            nc += dc[dir];
        }

        double avg = cost / distSum;
        double CR = 1+(avg-1.0)*(avg-1.0);
        // cerr << "CR " << CR << endl;
        nr = p[0];
        nc = p[1];
        int maxCnt = 0;

        for (int i = 0; i < ans.size(); ++i) {
            int dir = chToIdx[ans[i]];
            int opDir = oppDir[dir];

            double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
            double plus = avg * scalingFactor;
            double tmpR = min(0.7, R+0.003*cnt[nr][nc][dir]);
            maxCnt = max(maxCnt, cnt[nr][nc][dir]);
            ++cnt[nr][nc][dir];
            // if (cnt[nr][nc][dir] == 1) {
            //     expected[nr][nc][dir] = plus;
            // } else {
            // if (t > 5) {
            //     tmpR /= CR;
            // }
                expected[nr][nc][dir] = expected[nr][nc][dir]*tmpR + plus*(1.0-tmpR);
            // }

            int nextr = nr+dr[dir];
            int nextc = nc+dc[dir];

            if (nextr >= 0 && nextr < MAXN
            && nextc >= 0 && nextc < MAXN) {
                expected[nextr][nextc][opDir] = expected[nr][nc][dir];
                cnt[nextr][nextc][opDir] = cnt[nr][nc][dir];
            }

            nr = nextr;
            nc = nextc;
        }
        // cerr << "MAXCNT " << maxCnt << endl;
    }

    return 0;
}