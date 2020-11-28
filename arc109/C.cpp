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

using VI = vector <int>;
using VVI = vector <VI>;
// R : 0, P : 1, S : 2

int modPow(int n, int p, int MOD) {
    if (p == 0) {
        return 1;
    }

    int ret = modPow(n, p/2, MOD);
    ret = (ret * ret)%MOD;

    if (p%2 != 0) {
        ret = (ret * n) % MOD;
    }
    return ret;
}

inline int chToInt(char ch) {
    switch(ch) {
        case 'R': return 0;
        case 'P': return 1;
        default: return 2;
    }
}

char intToCh(int v) {
    switch(v) {
        case 0: return 'R';
        case 1: return 'P';
        default : return 'S';
    }
}

inline int winner(int l, int r) {
    if (l == r) {
        return l;
    } else {
        if (l > r) {
            swap(l, r);
        }

        if (l == 0) {
            if (r == 1) { // P wins
                return 1;
            } else { // R wins
                return 0;
            }
        } else if (l == 1) {
            if (r == 2) { // only possibility, S wins
                return 2;
            }
        }
    }

    return 0; // no way to reach
}

int solve(VVI& dp, const VI& num, int offset, int level) {
    if (level == 0) {
        return num[offset];
    }

    if (dp[offset][level] >= 0) {
        return dp[offset][level];
    }

    int &ret = dp[offset][level];
    int N = num.size();
    int newOffset = (offset + modPow(2, level-1, N))%N;

    int left = solve(dp, num, offset, level-1);
    int right = solve(dp, num, newOffset, level-1);

    return ret = winner(left, right);
}

int main() {
    int N;
    int K;
    cin >> N >> K;

    VI num(N);
    VVI dp(N, VI(K+1, -1));

    string S;
    cin >> S;

    for (int i = 0; i < N; ++i) {
        num[i] = chToInt(S[i]);
    }

    int w = solve(dp, num, 0, K);

    cout << intToCh(w) << endl;

    return 0;
}