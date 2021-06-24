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

int solve(const VVI& line, VVI& dp, int l, int r) {
    if (l > r) {
        return 0;
    }

    if (dp[l][r] >= 0) {
        return dp[l][r];
    }

    UMI gnum;

    for (int i = 0; i < line.size(); ++i) {
        if (line[i][0] >= l && line[i][1] <= r) {
            int res = solve(line, dp, l, line[i][0]-1) ^ solve(line, dp, line[i][1]+1, r);
            ++gnum[res];
        }
    }

    for (int v = 0; v <= gnum.size(); ++v) {
        if (gnum[v] == 0) {
            return dp[l][r] = v;
        }
    }

    return dp[l][r] = gnum.size()+1;
}

int main() {
    int TC;
    cin >> TC;

    while (TC--) {
        int N;
        cin >> N;

        VVI line(N, VI(2));
        const int MAXV = 110;
        VVI dp(MAXV, VI(MAXV, -1));

        for (int i = 0; i < N; ++i) {
            cin >> line[i][0] >> line[i][1];
            --line[i][1];
        }

        cout << (solve(line, dp, 1, 100) == 0 ? "Bob" : "Alice") << endl;
    }

    return 0;
}