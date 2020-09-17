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

const long long MOD = 1000000000LL + 7;
using VLL = vector <long long>;
using VVLL = vector <VLL>;

int main() {
    int S;
    cin >> S;

    long long ans = 0;
    int num = S/3;

    int upper = 2*S;
    VVLL C(upper+1, VLL(upper+1));

    for (int i = 0; i < upper; ++i) {
        C[i][i] = C[i][0] = 1;

        for (int j = 1; j < i; ++j) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
        }
    }

    for (int n = 1; n <= num; ++n) {
        int remain = S - 3*n;
        // H remain n
        // = C(n+remain-1) n-1
        ans += C[n+remain-1][n-1];
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}