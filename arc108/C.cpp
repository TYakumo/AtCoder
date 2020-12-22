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
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VSI = vector <set<int>>;

const int UNVISITED = -2;
const int VISITED = 0;

bool isVisited(const VI& color, int n) {
    return color[n] == VISITED || color[n] > 0;
}

inline void addForbidden(int now, VSI& forbidden, VI& color, const VVVI& adja) {
    int &nowc = color[now];

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i][0];
        int nextc = adja[now][i][1];

        if (nextc == nowc) {
            forbidden[nextv].insert(nowc);
        }
    }
}

void solve(int now, VSI& forbidden, VI& color, const VVVI& adja) {
    int &nowc = color[now];

    if (nowc == UNVISITED) {
        nowc = VISITED;
    }

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i][0];
        int nextc = adja[now][i][1];

        if (color[nextv] == UNVISITED) {
            if (nowc == VISITED && forbidden[now].count(nextc) == 0) { // not decided yet
                nowc = nextc;
                addForbidden(now, forbidden, color, adja);
            } else if (forbidden[nextv].count(nextc) == 0) {
                color[nextv] = nextc;
                addForbidden(nextv, forbidden, color, adja);
            }

            if (nowc == nextc || color[nextv] == nextc) {
                solve(nextv, forbidden, color, adja);
            }
        }
    }

    if (nowc == VISITED) { // still not visited
        auto iter = forbidden[now].begin();
        if (*iter != 1) {
            nowc = *iter-1;
        } else {
            auto nextIter = iter;

            while (iter != forbidden[now].end()) {
                ++nextIter;
                if (*nextIter != *iter+1) {
                    nowc = *nextIter - 1;
                    break;
                }

                iter = nextIter;
            }
        }

        if (nowc == VISITED) { //*(forbidden[now].end()-1) != N
            nowc = color.size();
        }
    }
}


int main() {
    int N;
    int M;

    cin >> N >> M;

    VVVI adja(N);
    VI color(N, UNVISITED);
    VSI forbidden(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        int c;
        cin >> f >> t >> c;
        --f;
        --t;

        adja[f].push_back({t, c});
        adja[t].push_back({f, c});
    }

    solve(0, forbidden, color, adja);

    for (int i = 0; i < color.size(); ++i) {
        cout << color[i] << endl;
    }

    return 0;
}