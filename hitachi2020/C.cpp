#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

void group(VVI& adja, VVI& groups, VI& colors, int now, int color) {

    colors[now] = color;
    groups[color].push_back(now);

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (colors[nextv] == -1) {
            group(adja, groups, colors, nextv, (color+1)%2);
        }
    }
}

void color(VI& res, VI& set1, VI& set2) {
    int N = res.size();
    vector <int> cnt(3);
    vector <int> maxVal(3);
    cnt[0] = 3;
    cnt[1] = 1;
    cnt[2] = 2;

    maxVal[0] = N/3 * 3;
    maxVal[1] = (N-1)/3 * 3 + 1;
    maxVal[2] = (N-2)/3 * 3 + 2;

    if (set1.size() <= N/3) {
        for (int i = 0; i < set1.size(); ++i) {
            res[set1[i]] = cnt[0];
            cnt[0] += 3;
        }

        int idx = 0;
        for (int i = 0; i < 3; ++i) {
            while (cnt[i] <= maxVal[i]) {
                res[set2[idx++]] = cnt[i];
                cnt[i] += 3;
            }
        }
    } else {
        vector <int> idx(2);
        // #mod 2 <= #mod 1, and |set1| <= |set2|

        while (cnt[2] <= maxVal[2]) {
            res[set1[idx[0]++]] = cnt[2];
            cnt[2] += 3;
        }

        while (cnt[1] <= maxVal[1]) {
            res[set2[idx[1]++]] = cnt[1];
            cnt[1] += 3;
        }

        while (idx[0] < set1.size()) {
            res[set1[idx[0]++]] = cnt[0];
            cnt[0] += 3;
        }

        while (idx[1] < set2.size()) {
            res[set2[idx[1]++]] = cnt[0];
            cnt[0] += 3;
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    VVI adja(N);
    VVI groups(2);
    VI colors(N, -1);
    VI res(N);

    int root = 0;

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        scanf("%d %d", &f, &t);
        --f;
        --t;

        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    group(adja, groups, colors, root, 0);

    if (groups[0].size() < groups[1].size()) {
        color(res, groups[0], groups[1]);
    } else {
        color(res, groups[1], groups[0]);
    }

    cout << res[0];
    for (int i = 1; i < res.size(); ++i) {
        cout << " " << res[i] ;
    }
    cout << endl;

    return 0;
}