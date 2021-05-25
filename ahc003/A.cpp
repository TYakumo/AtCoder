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

using VS = vector <string>;

const int MAXN = 30;
const int RND_MAXN = 200000;
VI rndVal(RND_MAXN);

struct Queue {
    int r;
    int c;
    double cost;

    Queue (int pr, int pc, double dcost) : r(pr), c(pc), cost(dcost) {}
    bool operator<(const Queue& q) const {
        if (cost != q.cost) {
            return cost > q.cost;
        }

        if (r != q.r) {
            return r < q.r;
        }

        return c < q.c;
    }
};

inline double sigmoid (double v) {
    return 1.0 / (1.0 + exp(-v));
}

inline double probConvert(double p) {
    // return p;
    return sqrt(p);
    // double diff = p-1;
    // double prob = sigmoid(diff*2);

    // if (prob > 0.8) {
    //     return sqrt(p);
    // } else if (prob < 0.2) {
    //     return sqrt(p);
    // }

    // return 1.0;
}

int main() {
    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};
    const char dch[] = {'D', 'U', 'R', 'L'};
    const int oppDir[] = {1, 0, 3, 2};
    unordered_map <char, int> chToIdx;

    for (int i = 0; i < 4; ++i) {
        chToIdx[dch[i]] = i;
    }

    const double FACTOR = 1.2;
    // const double INIT_VALUE = 5000/FACTOR;
    const double INIT_VALUE = 5000;
    const double INF = 1e+18;
    const int TIMES = 1000;
    const double R = 0.4;
    VVVD expected(MAXN, VVD(MAXN, VD(4, INIT_VALUE)));
    VVVI cnt(MAXN, VVI(MAXN, VI(4)));
    double costAvg = INIT_VALUE;
    VVI p(TIMES, VI(4));
    VS ans(TIMES);
    VD cost(TIMES);

    random_device seed_gen;
    mt19937 engine(seed_gen());

    for (int i = 0; i < RND_MAXN; ++i) {
        rndVal[i] = engine()%300;
    }

    double emptyAvg = 0;
    int emptyCnt = 0;
    const double SCALING_LOWER = 0.85;
    const double SCALING_UPPER = 1.15;
    const int THRESHOLD = 50;

    for (int t = 0; t < TIMES; ++t) {
        cin >> p[t][0] >> p[t][1] >> p[t][2] >> p[t][3];
        VVD dp(MAXN, VD(MAXN, INF));
        VVI pre(MAXN, VI(MAXN, -1));
        VVI used(MAXN, VI(MAXN));
        VVVD localExpected = expected;
        priority_queue<Queue> pq;
        dp[p[t][0]][p[t][1]] = 0;
        pq.push(Queue(p[t][0], p[t][1], 0));

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

            if (nr == p[t][2] && nc == p[t][3]) {
                break;
            }

            used[nr][nc] = 1;

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
        int nr = p[t][2];
        int nc = p[t][3];

        while (nr != p[t][0] || nc != p[t][1]) {
            int dir = pre[nr][nc];
            // cerr << "NOW " << nr << " " << nc << " " << dir << endl;
            ans[t] += dch[dir];
            nr -= dr[dir];
            nc -= dc[dir];
        }

        // cerr << "END TRACING" << endl;
        reverse(ans[t].begin(), ans[t].end());
        cout << ans[t] << endl;

        cin >> cost[t];
        costAvg = costAvg*R + cost[t]*(1.0-R);
        cost[t] *= FACTOR;

        // update
        if (t > 20 && t%10 == 0) {
            VVVD newExpected = expected;

            for (int ct = 0; ct < t; ++ct) {
                nr = p[ct][0];
                nc = p[ct][1];
                double distSum = 0;

                for (int i = 0; i < ans[ct].size(); ++i) {
                    int dir = chToIdx[ans[ct][i]];

                    double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
                    distSum += scalingFactor;
                    nr += dr[dir];
                    nc += dc[dir];
                }

                double avg = cost[ct] / distSum;

                nr = p[ct][0];
                nc = p[ct][1];

                for (int i = 0; i < ans[ct].size(); ++i) {
                    int dir = chToIdx[ans[ct][i]];
                    int opDir = oppDir[dir];

                    double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
                    double plus = avg * scalingFactor;
                    newExpected[nr][nc][dir] += plus;

                    int nextr = nr+dr[dir];
                    int nextc = nc+dc[dir];

                    if (nextr >= 0 && nextr < MAXN
                    && nextc >= 0 && nextc < MAXN) {
                        newExpected[nextr][nextc][opDir] = newExpected[nr][nc][dir];
                    }

                    nr = nextr;
                    nc = nextc;
                }
            }

            for (int i = 0; i < MAXN; ++i) {
                for (int j = 0; j < MAXN; ++j) {
                    for (int dir = 0; dir < 4; ++dir) {
                        newExpected[i][j][dir] /= (cnt[i][j][dir]+1);
                    }
                }
            }

            expected = newExpected;
        }

        nr = p[t][0];
        nc = p[t][1];
        double distSum = 0;
        double okRatio = 0;
        int okCount = 0;

        for (int i = 0; i < ans[t].size(); ++i) {
            int dir = chToIdx[ans[t][i]];

            double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
            if (cnt[nr][nc][dir] != 0) {
                okRatio += 1.0 / ans[t].size();
                ++okCount;
            }
            distSum += scalingFactor;

            nr += dr[dir];
            nc += dc[dir];
        }

        double avg = cost[t] / distSum;
        double costScaling = 1.0;
        if (okRatio >= 0.3) {
            // costScaling = max(SCALING_LOWER, min(SCALING_UPPER, probConvert(avg)));
            avg /= costScaling;
        }
        // cerr << "SCALING " <<  max(SCALING_LOWER, min(SCALING_UPPER, sqrt(avg))) << " " << avg << endl;

        double CR = 1+(avg-1.0)*(avg-1.0);
        // cerr << "CR " << CR << endl;
        // cerr << "avg ratio " << avg << endl;
        nr = p[t][0];
        nc = p[t][1];
        int maxCnt = 0;

        for (int i = 0; i < ans[t].size(); ++i) {
            int dir = chToIdx[ans[t][i]];
            int opDir = oppDir[dir];

            double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
            double plus = avg * scalingFactor;
            maxCnt = max(maxCnt, cnt[nr][nc][dir]);

            if (cnt[nr][nc][dir] == 0) {
                emptyAvg *= emptyCnt;
                emptyAvg += plus;
                ++emptyCnt;
                emptyAvg /= emptyCnt;
            }

            ++cnt[nr][nc][dir];
            if (cnt[nr][nc][dir] >= THRESHOLD) {
                plus *= costScaling; // revert
                expected[nr][nc][dir] *= (cnt[nr][nc][dir]-1);
                expected[nr][nc][dir] += plus;
                expected[nr][nc][dir] /= cnt[nr][nc][dir];
            } else {
                expected[nr][nc][dir] = expected[nr][nc][dir]*R + plus*(1.0-R);
            }


            int nextr = nr+dr[dir];
            int nextc = nc+dc[dir];
            expected[nr][nc][dir] = max(2000.0, min(8000.0, expected[nr][nc][dir]));

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

    // cerr << "DEBUG " << emptyAvg << endl;

    return 0;
}