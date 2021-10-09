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
using VVVLL = vector <VVLL>;
using VVVVLL = vector <VVVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

int findIdx(const VVLL& adja, long long timing, int offset) {
    int ret = -1;
    int low = 0;
    int up = adja.size() - 1;

    while (low <= up) {
        int mid = (low + up) / 2;

        if (timing <= adja[mid][offset]) {
            ret = mid;
            up = mid-1;
        } else {
            low = mid+1;
        }
    }

    return ret;
}

int findStartIdx(const VVLL& adja, long long timing) {
    return findIdx(adja, timing, 0);
}

int main() {
    int N;
    int M;
    int Q;
    cin >> N >> M >> Q;

    VVVLL adja(N);
    for (int i = 0; i < M; ++i) {
        int a;
        int b;
        long long s;
        long long t;
        cin >> a >> b >> s >> t;
        --a;
        --b;
        adja[a].push_back({s, t, b});
    }

    // precalculation
    const int LOGM = 20;
    VVVVLL precal(LOGM, VVVLL(N));
    for (int i = 0; i < N; ++i) {
        sort(adja[i].begin(), adja[i].end());
        precal[0][i] = adja[i];
    }

    for (int l = 1; l < LOGM; ++l) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < precal[l-1][i].size(); ++j) {
                int preNextv = precal[l-1][i][j][2];
                long long nowTime = precal[l-1][i][j][1];

                if (preNextv != -1) {
                    int idx = findStartIdx(precal[l-1][preNextv], nowTime);
                    if (idx != -1) {
                        long long nextt = precal[l-1][preNextv][idx][1];
                        int nextv = precal[l-1][preNextv][idx][2];
                        precal[l][i].push_back({precal[l-1][i][j][0], nextt, nextv});
                    } else {
                        precal[l][i].push_back(precal[l-1][i][j]);
                    }
                }
            }
        }
    }

    // solution
    for (int q = 0; q < Q; ++q) {
        long long x;
        int y;
        long long z;
        cin >> x >> y >> z;
        --y;

        for (int l = LOGM-1; l >= 0; --l) {
            int idx = findStartIdx(precal[l][y], x);
            if (idx != -1 && z > precal[l][y][idx][1]) {
                x = precal[l][y][idx][1];
                y = precal[l][y][idx][2];
            }
        }

        int idx = findStartIdx(precal[0][y], x);

        if (idx == -1) {
            cout << y+1 << endl;
        } else {
            if (z > precal[0][y][idx][0] && z <= precal[0][y][idx][1]) {
                cout << y+1 << " " << precal[0][y][idx][2]+1 << endl;
            } else {
                cout << y+1 << endl;
            }
        }
    }

    return 0;
}