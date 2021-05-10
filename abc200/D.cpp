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


int main() {
    int N;
    cin >> N;
    VI A(N+10);
    const int MOD = 200;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        A[i] %= MOD;
    }

    VVVI dp(N+10, VVI(N+10, VI(MOD)));
    VVVI flag(N+10, VVI(N+10, VI(MOD)));
    VVVI prev(N+10, VVI(N+10, VI(MOD)));
    dp[0][0][0] = 1;

    // init
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int d = 0; d < MOD; ++d) {
                if (dp[i][j][d] == 0) {
                    continue;
                }

                // chosen
                if (i != j) {
                    int newd = (d+(A[i]-A[j])) % MOD;
                    newd = (newd+MOD)%MOD;
                    dp[i+1][j+1][newd] = 1;
                    prev[i+1][j+1][newd] = 3;
                    flag[i+1][j+1][newd] = 1;
                }

                // discard i
                if (flag[i+1][j][d] == 0 || flag[i][j][d]){
                    dp[i+1][j][d] = 1;
                    prev[i+1][j][d] = 1;
                    flag[i+1][j][d] = flag[i][j][d];
                }

                // discard j
                if (flag[i][j+1][d] == 0 || flag[i][j][d]) {
                    dp[i][j+1][d] = 1;
                    prev[i][j+1][d] = 2;
                    flag[i][j+1][d] = flag[i][j][d];
                }

                // choose i only
                int newd = (d+A[i]) % MOD;
                if (flag[i][j][d]){
                    dp[i+1][j][newd] = 1;
                    prev[i+1][j][newd] = 4;
                    flag[i+1][j][newd] = flag[i][j][d];
                }

                // choose j only
                newd = (d-A[j]+MOD) % MOD;
                if (flag[i][j][d]){
                    dp[i][j+1][newd] = 1;
                    prev[i][j+1][newd] = 5;
                    flag[i][j+1][newd] = flag[i][j][d];
                }
            }
        }
    }

    VVI ans(2);

    for (int i = 0; i <= N && ans[0].empty(); ++i) {
        for (int j = 0; j <= N && ans[0].empty(); ++j) {
            if (flag[i][j][0] == 0) {
                continue;
            }

            int ni = i;
            int nj = j;
            int nd = 0;

            while (prev[ni][nj][nd] && ni >= 0 && nj >= 0) {
                if (prev[ni][nj][nd] == 3) {
                    --ni;
                    --nj;
                    ans[0].push_back(ni);
                    ans[1].push_back(nj);
                    nd -= (A[ni] - A[nj]);
                    nd = (nd%MOD + MOD) % MOD;
                } else if (prev[ni][nj][nd] == 1) {
                    --ni;
                } else if (prev[ni][nj][nd] == 2) {
                    --nj;
                } else if (prev[ni][nj][nd] == 4) {
                    --ni;
                    ans[0].push_back(ni);
                    nd -= A[ni];
                    nd = (nd%MOD + MOD) % MOD;
                } else {
                    --nj;
                    ans[1].push_back(nj);
                    nd += A[nj];
                    nd = (nd%MOD + MOD) % MOD;
                }
            }
        }
    }

    if (ans[0].empty()) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for (int i = 0; i < 2; ++i) {
            cout << ans[i].size();
            sort(ans[i].begin(), ans[i].end());
            for (int j = 0; j < ans[i].size(); ++j) {
                cout << " " << ans[i][j]+1;
            }
            cout << endl;
        }
    }

    return 0;
}