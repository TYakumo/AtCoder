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
const int MAXN = 50;
const int INF = 100000000;
const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};
const char dir[] = {'D', 'U', 'R', 'L'};
int tried = 0;
bool endFlag = false;

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

int findPotential(const VVMI& bestv, int r, int c, int d) {
    if (bestv[r][c].empty()) {
        return INF;
    }

    auto iter = bestv[r][c].lower_bound(d);

    if (iter == bestv[r][c].begin() && d < iter->first) {
        return INF;
    }

    if (iter == bestv[r][c].end()) {
        --iter;
    }

    int ret = iter->second;
    const int HLIMIT = 2;

    while (true) {
        if (d-iter->first <= HLIMIT) {
            ret = max(ret, iter->second);
        } else {
            break;
        }

        if (iter == bestv[r][c].begin()) {
            break;
        }
        --iter;
    }

    return ret;
}

int solve(const VVI& val, const VVI& group, VI& gused, VVMI& bestv, int r, int c, int depth, int sum, int& best, VC& path, VC& ansPath) {
    ++tried;

    if (endFlag) {
        if (sum > best) {
            best = sum;
            ansPath = path;
        }
        return val[r][c];
    }

    if (tried%10000 == 0) {
        if (timer.elapses()) {
            endFlag = true;
            return val[r][c];
        }
    }

    auto valid = [](int r, int c) { return r >= 0 && r < MAXN && c >= 0 && c < MAXN; };

    ++gused[group[r][c]];
    VVI pcho;
    int ret = val[r][c];

    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (valid(nr, nc) && gused[group[nr][nc]] == 0) {
            int minDist = min(min(MAXN-nr-1, nr), min(MAXN-nc-1, nc));
            pcho.push_back({minDist, d});
        }
    }

    sort(pcho.begin(), pcho.end());

    for (int pi = 0; pi < pcho.size(); ++pi) {
        int d = pcho[pi][1];
        int nr = r + dr[d];
        int nc = c + dc[d];

        int potential = findPotential(bestv, nr, nc, depth+1);

        if (sum + potential > best) {

            path.push_back(dir[d]);
            ret = max(ret, val[r][c] + solve(val, group, gused, bestv, nr, nc, depth+1, sum + val[nr][nc], best, path, ansPath));
            path.pop_back();
        }
    }

    if (pcho.size() == 0) {
        if (sum > best) {
            best = sum;
            ansPath = path;
        }
    }

    bestv[r][c][depth] = max(bestv[r][c][depth], ret);
    --gused[group[r][c]];
    return ret;
}

int main() {
    int sr;
    int sc;
    cin >> sr >> sc;

    VVI val(MAXN, VI(MAXN));
    VVI group(MAXN, VI(MAXN));
    VI gused(MAXN*MAXN);
    VVMI bestv(MAXN, VMI(MAXN));
    VC path;
    VC ansPath;
    int best = 0;

    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            cin >> group[i][j];
        }
    }

    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            cin >> val[i][j];
        }
    }

    timer.measure();
    timer.limit = 1.75;
    solve(val, group, gused, bestv, sr, sc, 0, val[sr][sc], best, path, ansPath);

    for (int i = 0; i < ansPath.size(); ++i) {
        cout << ansPath[i];
    }
    cout << endl;
    // cerr << tried << endl;
    // cerr << best << endl;

    return 0;
}