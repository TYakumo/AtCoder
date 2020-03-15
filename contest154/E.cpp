#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
const int MAXS = 200;

using VVI = vector<vector<int>>;
using VVVI = vector<VVI>;
VVVI dp;

int solve(string& str, int now, bool smaller, int nonZero, int K) { // notice that K >= 1 && 0 is illegal, so no special handling needed
    if (now == str.size()) {
        return (int)(nonZero == K);
    }

    if (dp[now][smaller][nonZero] >= 0) {
        return dp[now][smaller][nonZero];
    }

    int ret = 0;
    int c = str[now] - '0';
    int nzd = 0; //non zero digit

    for (int d = 0; d < 10; ++d) {
        if (d == 0 || nonZero < K) {
            if (smaller || d <= c) {
                ret += solve(str, now+1, smaller || (d < c), nonZero + nzd, K);
            }
        }
        nzd = 1;
    }

    return dp[now][smaller][nonZero] = ret;
}

int main() {
    string str;
    int K;

    cin >> str;
    cin >> K;

    dp = std::forward<VVVI>(VVVI(str.size(), VVI(2, vector<int>(K+1, -1))));

    cout << solve(str, 0, false, 0, K) << endl;
}