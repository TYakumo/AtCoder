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

using VLL = vector <long long>;
using VVLL = vector <VLL>;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    long long A;
    long long B;
    cin >> A >> B;

    VLL primesList = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71}; // p <= 72
    unordered_map <long long, long long> pMask;

    for (long long n = A; n <= B; ++n) {
        pMask[n] = 0;
        for (int j = 0; j < primesList.size(); ++j) {
            if (gcd(n, primesList[j]) != 1) {
                pMask[n] |= 1<<j;
            }
        }
    }

    int UPPER = 1 << primesList.size();

    VVLL dp(2, VLL(UPPER));
    dp[0][0] = dp[1][0] = 1;

    for (long long n = A; n <= B; ++n) {
        for (int i = 0; i < UPPER; ++i) {
            if ((i & pMask[n]) == 0) {
                dp[1][i | pMask[n]] += dp[0][i];
            }
        }
        dp[0] = dp[1];
    }

    long long ans = 0;
    for (int i = 0; i < UPPER; ++i) {
        ans += dp[0][i];
    }

    cout << ans << endl;

    return 0;
}