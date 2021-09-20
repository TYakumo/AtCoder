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
const long long MOD = 998244353;

int main() {
    int N;
    int M;
    int K;

    cin >> N >> M >> K;

    VVLL dp(N, VLL(K+1));
    VLL sum(K+1);
    VVI adja(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        --f;
        --t;
        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    sum[0] = 1;
    dp[0][0] = 1;

    for (int k = 1; k <= K; ++k) {
        for (int n = 0; n < N; ++n) {
            dp[n][k] = sum[k-1] - dp[n][k-1]; // all except self

            for (int i = 0; i < adja[n].size(); ++i) {
                int t = adja[n][i];
                dp[n][k] -= dp[t][k-1];
                dp[n][k] %= MOD;
            }
        }

        for (int n = 0; n < N; ++n) {
            sum[k] += dp[n][k];
            sum[k] %= MOD;
        }
    }

    cout << (dp[0][K]+MOD)%MOD << endl;

    return 0;
}