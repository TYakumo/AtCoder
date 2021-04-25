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

void solve(const VVI& adja, const VI& cand, VVI& ncolor, int now, long long& ans) {
    int N = cand.size();

    if (now == N) {
        ++ans;
        return ;
    }

    int nnow = cand[now];

    for (int c = 0; c < 3; ++c) {
        if (ncolor[nnow][c] == 0) {
            for (int i = 0; i < adja[nnow].size(); ++i) {
                int nextv = adja[nnow][i];
                ++ncolor[nextv][c];
            }

            solve(adja, cand, ncolor, now+1, ans);

            for (int i = 0; i < adja[nnow].size(); ++i) {
                int nextv = adja[nnow][i];
                --ncolor[nextv][c];
            }
        }
    }
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    VVI ncolor(N, VI(3));
    VVI adja(N);
    VI used(N);

    UnionAndFind ut(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;
        adja[f].push_back(t);
        adja[t].push_back(f);
        ut.unionGroup(f, t);
    }

    long long ans = 1;
    for (int i = 0; i < N; ++i) {
        if (used[i] == 0) {
            VI cand;
            cand.push_back(i);
            used[i] = 1;
            long long res = 0;

            for (int j = 0; j < N; ++j) {
                if (i != j && ut.findGroup(i) == ut.findGroup(j)) {
                    used[j] = 1;
                    cand.push_back(j);
                }
            }

            solve(adja, cand, ncolor, 0, res);
            ans *= res;
        }
    }


    cout << ans << endl;

    return 0;
}