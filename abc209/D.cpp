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

void traverse(const VVI& adja, VVI& parent, VI& depth, int now, int d) {
    depth[now] = d;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (depth[nextv] == -1) {
            parent[nextv][0] = now;
            traverse(adja, parent, depth, nextv, d+1);
        }
    }
}

int main() {
    int N;
    int Q;
    cin >> N >> Q;

    const int MAXL = 20;
    VVI adja(N);
    VVI parent(N, VI(MAXL));
    VI depth(N, -1);

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;

        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    traverse(adja, parent, depth, 0, 0);

    for (int l = 1; l < MAXL; ++l) {
        for (int i = 0; i < N; ++i) {
            int p = parent[i][l-1];
            parent[i][l] = parent[p][l-1];
        }
    }

    for (int i = 0; i < Q; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --a;
        --b;

        int dist = 0;

        if (a != b) {
            if (depth[a] > depth[b]) {
                swap(a, b);
            }

            int diff = depth[b]-depth[a];
            dist = diff;
            for (int l = 0; l < MAXL; ++l) {
                if (diff & (1<<l)) {
                    b = parent[b][l];
                }
            }

            for (int l = MAXL-1; l >= 0; --l) {
                if (parent[a][l] != parent[b][l]) {
                    a = parent[a][l];
                    b = parent[b][l];
                    dist += 2*(1<<l);
                }
            }


            if (a != b) {
                dist += 2;
            }
        }

        if (dist%2 == 0) {
            cout << "Town" << endl;
        } else {
            cout << "Road" << endl;
        }
    }

    return 0;
}