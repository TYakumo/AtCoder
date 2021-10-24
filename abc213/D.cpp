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

void solve(const VVI& adja, VI& used, VI& ans, int now) {
    ans.push_back(now);
    used[now] = 1;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (!used[nextv]) {
            solve(adja, used, ans, nextv);
            // go back here
            ans.push_back(now);
        }
    }
}

int main() {
    int N;
    cin >> N;
    VVI adja(N);

    for (int i = 1; i < N; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --a;
        --b;
        adja[a].push_back(b);
        adja[b].push_back(a);
    }

    for (int i = 0; i < N; ++i) {
        sort(adja[i].begin(), adja[i].end());
    }

    VI used(N);
    VI ans;
    solve(adja, used, ans, 0);

    cout << 1;
    for (int i = 1; i < ans.size(); ++i) {
        cout << " " << ans[i]+1;
    }
    cout << endl;

    return 0;
}