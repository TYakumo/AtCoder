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
    const double LOWER_WEIGHT = 500.0;
    const double UPPER_WEIGHT = 12000.0;
    VVVD expected(MAXN, VVD(MAXN, VD(4, INIT_VALUE)));
    VVVI cnt(MAXN, VVI(MAXN, VI(4)));
    double costAvg = INIT_VALUE;
    VVI p(TIMES, VI(4));
    VS ans(TIMES);
    VD cost(TIMES);

    double emptyAvg = 0;
    double edgeAvg = 0;
    int emptyCnt = 0;
    int edgeCnt = 0;
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

        int tmpCnt = 0;
        emptyAvg = 0;

        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                for (int dir = 0; dir < 4; ++dir) {
                    if (cnt[i][j][dir] > 0) {
                        ++tmpCnt;
                        emptyAvg += localExpected[i][j][dir];
                    }
                }
            }
        }

        if (tmpCnt > 0) {
            emptyAvg /= tmpCnt;
            if (t > 3) {
                for (int i = 0; i < MAXN; ++i) {
                    for (int j = 0; j < MAXN; ++j) {
                        for (int dir = 0; dir < 4; ++dir) {
                            if (cnt[i][j][dir] == 0) {
                                // expected[i][j][dir] = localExpected[i][j][dir] = min(localExpected[i][j][dir], emptyAvg*5.0/6);
                                // localExpected[i][j][dir] = min(localExpected[i][j][dir], emptyAvg*5.0/6);
                                localExpected[i][j][dir] = emptyAvg*5.0/6;
                            }
                        }
                    }
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
                // double cost = dp[nr][nc] + expected[nr][nc][dir];
                double cost = dp[nr][nc] + localExpected[nr][nc][dir];

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
        edgeCnt += ans[t].size();
        edgeAvg += cost[t];
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
                        double weight = cnt[i][j][dir] * max(0.0, (double)(t)/TIMES);
                        newExpected[i][j][dir] += weight * expected[i][j][dir];
                        newExpected[i][j][dir] /= (weight + cnt[i][j][dir]+1);
                        newExpected[i][j][dir] = max(LOWER_WEIGHT, min(UPPER_WEIGHT, newExpected[i][j][dir]));
                    }
                }
            }

            expected = newExpected;
        }

        nr = p[t][0];
        nc = p[t][1];
        double distSum = 0;

        for (int i = 0; i < ans[t].size(); ++i) {
            int dir = chToIdx[ans[t][i]];

            double scalingFactor = cnt[nr][nc][dir] == 0 ? INIT_VALUE : expected[nr][nc][dir];
            distSum += scalingFactor;

            nr += dr[dir];
            nc += dc[dir];
        }

        double avg = cost[t] / distSum;
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
                expected[nr][nc][dir] *= (cnt[nr][nc][dir]-1);
                expected[nr][nc][dir] += plus;
                expected[nr][nc][dir] /= cnt[nr][nc][dir];
            } else {
                expected[nr][nc][dir] = expected[nr][nc][dir]*R + plus*(1.0-R);
            }


            int nextr = nr+dr[dir];
            int nextc = nc+dc[dir];
            expected[nr][nc][dir] = max(LOWER_WEIGHT, min(UPPER_WEIGHT, expected[nr][nc][dir]));

            if (nextr >= 0 && nextr < MAXN
            && nextc >= 0 && nextc < MAXN) {
                expected[nextr][nextc][opDir] = expected[nr][nc][dir];
                cnt[nextr][nextc][opDir] = cnt[nr][nc][dir];
            }

            nr = nextr;
            nc = nextc;
        }
        // cerr << "MAXCNT " << maxCnt << endl;
        // cerr << t << " DEBUG EMPTY AVG " << emptyAvg << endl;
    }

    // cerr << "DEBUG EMPTY AVG " << emptyAvg << endl;
    // cerr << "DEBUG EDGE AVG " << edgeAvg/edgeCnt << endl;

    // for (int i = 0; i < MAXN; ++i) {
    //     for (int j = 0; j < MAXN; ++j) {
    //         cerr << (int)cnt[i][j][0] << " ";
    //     }
    //     cerr << endl;
    // }

    // for (int i = 0; i < MAXN; ++i) {
    //     for (int j = 0; j < MAXN; ++j) {
    //         cerr << (int)cnt[i][j][2] << " ";
    //     }
    //     cerr << endl;
    // }

    return 0;
}