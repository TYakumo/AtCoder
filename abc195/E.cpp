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
const int AWIN = 1;
const int TWIN = 2;

int findWinner(VVI& dp, const string& S, const string& X, int now, int remainder) {
    if (now == dp.size()) {
        if (remainder%7 == 0) {
            return TWIN;
        }
        return AWIN;
    }

    if (dp[now][remainder] != -1) {
        return dp[now][remainder];
    }

    int d = S[now]-'0';
    int &ret = dp[now][remainder];

    if (X[now] == 'A') {
        if (findWinner(dp, S, X, now+1, remainder*10%7) == AWIN) {
            return ret = AWIN;
        }

        if (findWinner(dp, S, X, now+1, (remainder*10+d) %7) == AWIN) {
            return ret = AWIN;
        }

        return ret = TWIN;
    } else {
        if (findWinner(dp, S, X, now+1, remainder*10%7) == TWIN) {
            return ret = TWIN;
        }

        if (findWinner(dp, S, X, now+1, (remainder*10+d) %7) == TWIN) {
            return ret = TWIN;
        }

        return ret = AWIN;
    }
}

int main() {
    int N;
    cin >> N;

    string S;
    string X;
    cin >> S >> X;

    VVI dp(S.size(), VI(8, -1));
    int getWinner = findWinner(dp, S, X, 0, 0);

    if (getWinner == AWIN) {
        cout << "Aoki" << endl;
    } else {
        cout << "Takahashi" << endl;
    }

    return 0;
}