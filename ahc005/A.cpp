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
#include <cassert>
#include <chrono>
using namespace std;

using VC = vector <char>;
using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using MI = map<int, int>;
using VMI = vector <MI>;
using VVMI = vector <VMI>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector<string>;

class timer {
    vector<timer> timers;
    int n = 0;
public:
    double limit = 5;
    double t = 0;
    timer() {}
    timer(int size) : timers(size) {}
    bool elapses() const {
        return time() - t > limit;
    }
    void measure() {
        t = time() - t;
        ++n;
    }
    void measure(char id) {
        timers[id].measure();
    }
    void print() {
        if (n % 2)
            measure();
        for (int i = 0; i < 128; ++i) {
            if (timers[i].n)
                cerr << (char)i << ' ' << timers[i].t << 's' << endl;
        }
        cerr << "  " << t << 's' << endl;
    }
    static double time() {
        using namespace chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / 1000.0;
    }
} timer(128);

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;

    UnionAndFind (int gSize) {
        groupSize = vector<int> (gSize, 1);
        groupParent = vector<int> (gSize, -1);
    }

    int findGroup(int n) {
        if (groupParent[n] == -1) {
            return n;
        }
        return groupParent[n] = findGroup(groupParent[n]);
    }

    void unionGroup(int x, int y) {
        y = findGroup(y);
        x = findGroup(x);

        if (x == y) {
            return ;
        }

        if (groupSize[x] > groupSize[y]) {
            swap(x, y);
        }

        groupSize[y] += groupSize[x];
        groupParent[x] = y;
    }
};

struct Que {
    int r;
    int c;
    int d;
    Que (int pr, int pc, int pd) : r(pr), c(pc), d(pd) {}

    bool operator<(const Que& q) const {
        return d > q.d;
    }
};

const int dr[] = {-1, 1,  0, 0};
const int dc[] = {0,  0, -1, 1};
const char dir[] = {'U', 'D', 'L', 'R'};
const int INF = 100000000;
VI order;

VVI getCand(const VS& S) {
    VVI cands;
    int N = S.size();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (S[i][j] != '@' && S[i][j] != '#') {
                cands.push_back({i, j, 0});
            }
        }
    }

    return cands;
}

VVI choosePoint(const VS& S, int sr, int sc) {
    VVI pnts;
    int N = S.size();
    VS tmp = S;

    auto valid = [&N](int r, int c){ return r >= 0 && r < N && c >= 0 && c < N; };

    for (int d = 0; d < 4; ++d) {
        int nr = sr;
        int nc = sc;

        while (valid(nr, nc)) {
            if (tmp[nr][nc] == '#') {
                break;
            }

            tmp[nr][nc] = '@';

            nr += dr[d];
            nc += dc[d];
        }
    }
    pnts.push_back({sr, sc});

    VVI cands = getCand(tmp);

    while (true) {
        int theMax = 0;
        int choIdx = -1;
        VS ttmp = tmp;

        for (int idx = 0; idx < cands.size(); ++idx) {
            int cnt = 0;
            int cr = cands[idx][0];
            int cc = cands[idx][1];

            for (int d = 0; d < 4; ++d) {
                int nr = cr;
                int nc = cc;

                while (valid(nr, nc)) {
                    if (ttmp[nr][nc] == '#') {
                        break;
                    }

                    if (ttmp[nr][nc] != '@') {
                        ++cnt;
                    }

                    ttmp[nr][nc] = '@';

                    nr += dr[d];
                    nc += dc[d];
                }
            }

            if (cnt > theMax) {
                theMax = cnt;
                choIdx = idx;
            } else if (cnt == 0) {
                cands[idx][2] = 1;
            }
        }

        if (theMax == 0) {
            break;
        }

        int fr = cands[choIdx][0];
        int fc = cands[choIdx][1];
        pnts.push_back({fr, fc});
        cands[choIdx][2] = 1;

        for (int d = 0; d < 4; ++d) {
            int nr = fr;
            int nc = fc;

            while (valid(nr, nc)) {
                if (tmp[nr][nc] == '#') {
                    break;
                }

                tmp[nr][nc] = '@';

                nr += dr[d];
                nc += dc[d];
            }
        }

        // clear zeroes & used
        int idx = 0;
        while (idx < cands.size()) {
            if (cands[idx][2]) {
                swap(cands.back(), cands[idx]);
                cands.pop_back();
            } else {
                ++idx;
            }
        }
    }

    return pnts;
}

void generatePath(const VS& S, const VVI& pnts, VVVI& adja, VVI& cost) {
    int P = pnts.size();
    int N = S.size();
    auto valid = [&N](int r, int c){ return r >= 0 && r < N && c >= 0 && c < N; };
    map <VI, int> idMap;

    for (int i = 0; i < pnts.size(); ++i) {
        idMap[{pnts[i][0], pnts[i][1]}] = i;
    }

    for (int src = 0; src < pnts.size(); ++src) {
        VVI dist(N, VI(N, INF));
        VVI pre(N, VI(N, -1));
        VVI used(N, VI(N));

        int sr = pnts[src][0];
        int sc = pnts[src][1];

        priority_queue <Que> que;
        dist[sr][sc] = 0;
        que.push({sr, sc, 0});

        while (!que.empty()) {
            int r = que.top().r;
            int c = que.top().c;
            que.pop();

            if (used[r][c]) {
                continue;
            }
            used[r][c] = 1;

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                int nd = dist[r][c] + (S[r][c]-'0');

                if (valid(nr, nc) && S[nr][nc] != '#'
                    && nd < dist[nr][nc]) {
                    dist[nr][nc] = nd;
                    que.push({nr, nc, nd});
                    pre[nr][nc] = d;
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (idMap.count({r, c})) {
                    int nr = r;
                    int nc = c;
                    int id = idMap[{r, c}];

                    while (nr != sr || nc != sc) {
                        int udir = pre[nr][nc];
                        adja[src][id].push_back(udir);
                        nr -= dr[udir];
                        nc -= dc[udir];
                    }

                    cost[src][id] = dist[r][c];
                    reverse(adja[src][id].begin(), adja[src][id].end());
                }
            }
        }
    }
}

VI solve(const VVVI& adja, const VVI& cost, int P, int& ans) {
    VI steps;
    VI used(P);
    int now = 0;
    int resCost = 0;
    used[0] = 1;

    for (int p = 1; p < P; ++p) {
        const int INF = 1000000000;
        int theMin = INF;
        int np = -1;

        for (int i = 0; i < P; ++i) {
            if (!used[i] && theMin > cost[now][i]) {
                np = i;
                theMin = cost[now][i];
            }
        }

        used[np] = 1;
        for (int i = 0; i < adja[now][np].size(); ++i) {
            steps.push_back(adja[now][np][i]);
        }
        resCost += cost[now][np];

        now = np;
    }

    for (int i = 0; i < adja[now][0].size(); ++i) {
        steps.push_back(adja[now][0][i]);
    }
    resCost += cost[now][0];
    ans = resCost;

    return steps;
}

int heuristic(const VVI& cost, VI& used) {
    int P = cost.size();
    int ret = 0;
    UnionAndFind ut(P);

    VVI edges;
    int minBack = INF;
    for (int i = 0; i < P; ++i) {
        if (used[i] && i) {
            ut.unionGroup(0, i);
        }

        if (!used[i]) {
            minBack = min(minBack, cost[i][0]);
        }

        for (int j = i+1; j < P; ++j) {
            if (!used[i] || !used[j]) {
                edges.push_back({cost[i][j], i, j});
            }
        }
    }

    sort(edges.begin(), edges.end());
    for (int e = 0; e < edges.size(); ++e) {
        int g1 = ut.findGroup(edges[e][1]);
        int g2 = ut.findGroup(edges[e][2]);

        if (g1 != g2) {
            ret += edges[e][0];
            ut.unionGroup(g1, g2);
        }
    }

    return ret + minBack;
}

void dfs(const VVVI& adja, const VVI& cost, int& ans, int now, int resCost, VI& used, VI& ansorder) {
    if (timer.elapses() || resCost >= ans) {
        return ;
    }

    int P = adja.size();
    if (order.size() == P) {
        resCost += cost[now][0];
        if (resCost < ans) {
            ans = resCost;
            ansorder.clear();
            order.push_back(0);

            for (int p = 1; p < order.size(); ++p) {
                int now = order[p-1];
                int np = order[p];
                for (int i = 0; i < adja[now][np].size(); ++i) {
                    ansorder.push_back(adja[now][np][i]);
                }
            }
            order.pop_back();
        }
        return ;
    }

    VVI cho;
    for (int np = 0; np < P; ++np) {
        if (!used[np]) {
            cho.push_back({cost[now][np], np});
        }
    }

    sort(cho.begin(), cho.end());

    for (int idx = 0; idx < cho.size(); ++idx) {
        int np = cho[idx][1];
        if (!used[np]) {
            used[np] = 1;
            order.push_back(np);
            int newcost = cost[now][np] + resCost;
            int hc = newcost; // + heuristic(cost, used);
            if (hc < ans) {
                dfs(adja, cost, ans, np, newcost, used, ansorder);
            }
            order.pop_back();
            used[np] = 0;
        }
    }
}

int main() {
    int N;
    cin >> N;

    int sr;
    int sc;
    VS S(N);

    cin >> sr >> sc;

    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    timer.measure();
    timer.limit = 2.7;
    int ans = INF;
    VVI pnts = choosePoint(S, sr, sc);
    VVVI adja(pnts.size(), VVI(pnts.size()));
    VVI cost(pnts.size(), VI(pnts.size()));
    generatePath(S, pnts, adja, cost);

    VI steps = solve(adja, cost, pnts.size(), ans);
    order = VI(1);

    VI used(pnts.size());
    used[0] = 1;
    dfs(adja, cost, ans, 0, 0, used, steps);

    for (int i = 0; i < steps.size(); ++i) {
        cout << dir[steps[i]];
    }
    cout << endl;

    return 0;
}