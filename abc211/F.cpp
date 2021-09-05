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
#include <atcoder/lazysegtree>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
const int MAXV = 101000;

int op(int a, int b) { return a + b; }
int e() { return 0; }
int mapping(int f, int x) { return f + x; }
int composition(int f, int g) { return f + g; }
int id() { return 0; }

using SG = atcoder::lazy_segtree<int, op, e, int, mapping, composition, id>;

enum class LType {
    LINE,
    QUERY
};

struct Line {
    int x;
    int sy;
    int ey;
    int sign;
    int idx;
    LType type;
    Line (int px, int psy, int pey, int ps, int pidx, LType pt) : x(px), sy(psy), ey(pey), sign(ps), idx(pidx), type(pt) {
    }

    bool operator<(const Line& l) const {
        return x < l.x;
    }
};

void processRect(vector <Line>& lines, const VVVI & rect) {
    SG sg(2*MAXV);
    for (int i = 0; i < rect.size(); ++i) {
        // group by x
        for (int st = 0; st < rect[i].size();) {
            int nx = rect[i][st][0];
            VVI pnts;
            int end = st+1;
            while (end < rect[i].size() && rect[i][end][0] == rect[i][st][0]) {
                ++end;
            }

            for (int j = st; j < end; ++j) {
                pnts.emplace_back(std::move(rect[i][j]));
            }

            st = end;

            for (int j = 0; j < pnts.size(); j += 2) {
                int sy = pnts[j][1];
                int ey = pnts[j+1][1];
                if (sg.get(sy) > 0) {
                    lines.emplace_back(Line(nx, sy, ey, -1, -1, LType::LINE));
                    sg.apply(sy, ey, -1);
                } else {
                    lines.emplace_back(Line(nx, sy, ey, 1, -1, LType::LINE));
                    sg.apply(sy, ey, 1);
                }
            }
        }
    }
}

void solve(const vector<Line>& lines, VI& ans) {
    SG sg(MAXV*2);
    for (int i = 0; i < lines.size(); ++i) {
        if (lines[i].type == LType::LINE) {
            sg.apply(lines[i].sy, lines[i].ey, lines[i].sign);
        } else {
            ans[lines[i].idx] += sg.get(lines[i].sy);
        }
    }
}

int main() {
    int N;
    cin >> N;

    VVVI rect(N);

    for (int i = 0; i < N; ++i) {
        int M;
        cin >> M;
        for (int j = 0; j < M; ++j) {
            int x;
            int y;
            cin >> x >> y;
            rect[i].push_back({x*2, y*2});
        }

        sort(rect[i].begin(), rect[i].end());
    }

    vector <Line> lines;
    processRect(lines, rect);

    int Q;
    cin >> Q;
    VI ans(Q);

    for (int q = 0; q < Q; ++q) {
        int x;
        int y;
        cin >> x >> y;
        lines.emplace_back(Line(x*2+1, y*2+1, y*2+1, 1, q, LType::QUERY));
    }

    sort(lines.begin(), lines.end());
    solve(lines, ans);

    for (int q = 0; q < Q; ++q) {
        cout << ans[q] << endl;
    }

    return 0;
}