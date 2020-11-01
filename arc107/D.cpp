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

const long long MOD = 998244353;
using VLL = vector <long long>;
using VVLL = vector <VLL>;

long long solve(VVLL& dp, int N, int K) {

    if (N == 0 && K == 0) {
        return 1;
    }

    if (K > N || N <= 0 || K <= 0) {
        return 0;
    }

    if (dp[N][K] >= 0) {
        return dp[N][K];
    }

    return dp[N][K] = (solve(dp, N-1, K-1) + solve(dp, N, 2*K))%MOD;
}

int main() {
    int N;
    int K;

    cin >> N >> K;

    VVLL dp(N+1, VLL(N+1, -1));
    // 3 nums = 1; 1/2, 1/4, 1/4 (depends on the leading terms)
    // 4 nums = 1; 1/2, 1/4, 1/4
    // 5 nums = 1; 1/4, 1/4, 1/4, 1/4
    // that is F(N) = 1
    // (2,4) => (1,2)+(1,2) or (1,1)+(1,3)

    cout << solve(dp, N, K) << endl;

    return 0;
}