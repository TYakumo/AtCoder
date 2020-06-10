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

int main() {
    int N;
    int S;
    cin >> N >> S;

    const long long MOD = 998244353;
    vector <long long> dp1(S+1);

    dp1[0] = 1;
    int sum = 0;

    for (int i = 0; i < N; ++i) {
        int v;
        cin >> v;

        vector <long long> dp2(S+1);

        for (int val = 0; val <= sum; ++val) {
            dp2[val] += dp1[val]*2;
            dp2[val] %= MOD;

            if (val+v <= S) {
                dp2[val+v] += dp1[val];
                dp2[val+v] %= MOD;
            }
        }

        sum = min(sum+v, S);
        dp1 = dp2;
    }

    cout << dp1[S] << endl;

    return 0;
}