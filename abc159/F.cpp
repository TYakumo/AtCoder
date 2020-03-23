#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N;
    int S;

    cin >> N >> S;

    const int MOD = 998244353;

    vector <int> val(N);
    vector<vector <int>> dp(N+1, vector<int>(S+1));

    for (int i = 0; i < N; ++i) {
        cin >> val[i];
    }

    dp[0][0] = 1;

    int sum = 0;
    int ans = 0;

    // f(1, 3, S) = f(1, 2, S) + f(1, 2, S-val[3])
    for (int i = 0; i < N; ++i) {
        dp[i+1][0] = 1;

        for (int j = 0; j <= sum; ++j) {
            int newVal = j + val[i];

            if (newVal <= S) {
                dp[i+1][newVal] = (dp[i+1][newVal] + dp[i][j]) % MOD;
            }

            dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;
        }

        sum = min(sum+val[i], S);
        ans = (ans + dp[i+1][S]) % MOD;
    }

    cout << ans << endl;

    return 0;
}