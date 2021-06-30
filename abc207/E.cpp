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


int main() {
    int N;
    cin >> N;

    VLL A(N);
    VLL sum(N);
    long long acc = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        acc += A[i];
        sum[i] = acc;
    }

    const long long MOD = 1000000000 + 7;
    VVLL dp(N+1, VLL(N+1));
    dp[0][0] = 1;

    long long ans = 0;
    for (int div = 1; div <= N; ++div) {
        VLL comb(div);
        comb[0] = dp[div-1][0];

        for (int st = 1; st <= N; ++st) {
            int remain = sum[st-1]%div;
            dp[div][st] = (dp[div][st] + comb[remain]) % MOD;
            comb[sum[st-1]%div] = (comb[sum[st-1]%div] + dp[div-1][st]) % MOD;
        }

        ans = (ans + dp[div][N])%MOD;
    }

    cout << ans << endl;


    return 0;
}