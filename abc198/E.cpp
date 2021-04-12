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

void solve(const VVI& adja, const VI& color, UMI& colorMap, VI& visited, VI& ok, int now) {
    if (colorMap[color[now]] > 0) {
        ok[now] = 0;
    }

    ++colorMap[color[now]];
    visited[now] = 1;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (visited[nextv] == 0) {
            solve(adja, color, colorMap, visited, ok, nextv);
        }
    }

    --colorMap[color[now]];
}

int main() {
    int N;
    cin >> N;

    VVI adja(N);
    VI color(N);

    for (int i = 0; i < N; ++i) {
        cin >> color[i];
    }

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        cin >> f >> t;

        adja[f-1].push_back(t-1);
        adja[t-1].push_back(f-1);
    }

    UMI colorMap;
    VI ok(N, 1);
    VI visied(N);

    solve(adja, color, colorMap, visied, ok, 0);

    for (int i = 0; i < N; ++i) {
        if (ok[i]) {
            cout << i+1 << endl;
        }
    }

    return 0;
}