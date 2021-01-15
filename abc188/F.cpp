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

using UMLL = unordered_map<long long, long long>;
const long long INF = 1000000000LL * 1000000000LL * 2;
long long solve(long long X, long long Y, UMLL& dp) {
    if (X >= Y || Y == 1) {
        return abs(X-Y);
    }

    if (dp.find(Y) != dp.end()) {
        return dp[Y];
    }

    long long ret = abs(X-Y);

    if (Y%2 == 0) {
        ret = min(ret, solve(X, Y/2, dp)+1);
    } else {
        ret = min(ret, 2+min(solve(X, (Y+1)/2, dp), solve(X, (Y-1)/2, dp)));
    }

    return dp[Y] = ret;
}

int main() {
    long long X;
    long long Y;
    cin >> X >> Y;

    UMLL dp;

    cout << solve(X, Y, dp) << endl;

    return 0;
}