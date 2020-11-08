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

int main() {
    string N;
    cin >> N;

    reverse(N.begin(), N.end());
    const int INF = 100000000;
    VVI dp(N.size()+1, VI(3, INF));

    for (int i = 0; i < N.size(); ++i) {
        int r = N[i]-'0';
        dp[i][r%3] = i;
    }

    for (int i = 0; i < N.size()-1; ++i) {
        int r = N[i+1]-'0';
        for (int j = 0; j < 3; ++j) {
            if (dp[i][j] != INF) {
                int newr = (j+r)%3;

                // chosen
                dp[i+1][newr] = min(dp[i+1][newr], dp[i][j]);

                // give up
                dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
            }
        }
    }

    cout << (dp[N.size()-1][0] == INF ? -1 : dp[N.size()-1][0]) << endl;

    return 0;
}