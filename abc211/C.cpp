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

const long long MOD = 1000000000+7;

int main() {
    string S;
    cin >> S;

    string str = "chokudai";
    VVLL dp(S.size()+1, VLL(str.size()+1));

    long long ans = 0;
    dp[0][0] = 1;
    for (int i = 0; i < S.size(); ++i) {
        for (int j = 0; j <= str.size(); ++j) {
            if (j < str.size() && dp[i][j] && str[j] == S[i]) {
                dp[i+1][j+1] += dp[i][j];
                dp[i+1][j+1] %= MOD;

                if (j == str.size()-1) {
                    ans += dp[i][j];
                    ans %= MOD;
                }
            }

            // skip this word
            dp[i+1][j] += dp[i][j];
            dp[i+1][j] %= MOD;
        }
    }

    cout << ans << endl;

    return 0;
}