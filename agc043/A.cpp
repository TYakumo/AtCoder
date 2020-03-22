#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    int R;
    int C;

    cin >> R >> C;
    vector <string> grid(R)
    ;
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
    }

    const int INF = 10000000;
    vector<vector<vector<int>>> dp(R, vector<vector<int>>(C, vector<int>(2, INF)));

    dp[0][0][grid[0][0] == '#'] = (grid[0][0] == '#');

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            int c = (grid[i][j] == '#');

            if (i) {
                dp[i][j][c] = min(dp[i][j][c], dp[i-1][j][c]);
                dp[i][j][c] = min(dp[i][j][c], dp[i-1][j][c^1] + c);
            }

            if (j) {
                dp[i][j][c] = min(dp[i][j][c], dp[i][j-1][c]);
                dp[i][j][c] = min(dp[i][j][c], dp[i][j-1][c^1] + c);
            }
        }
    }

    int c = (grid[R-1][C-1] == '#');
    cout << dp[R-1][C-1][c] << endl;

    return 0;
}