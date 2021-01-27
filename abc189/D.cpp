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
using VS = vector <string>;

int main() {
    int N;
    cin >> N;

    VVLL dp(N+1, VLL(2));
    VS c(N);


    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }

    // init y0
    dp[0][0] = dp[0][1] = 1;

    // yi
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k)  { // new x
                long long comb = dp[i][j];

                if (c[i] == "AND") {
                    int res = j&k;
                    dp[i+1][res] += comb;
                } else {
                    int res = j|k;
                    dp[i+1][res] += comb;
                }
            }
        }
    }

    cout << dp[N][1] << endl;

    return 0;
}