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

inline int getBlockStart(int npos, int bakPos) {
    int nextBlock = (bakPos+1-2)/3 * 3 + 2;
    return npos < 0 ? nextBlock : max(nextBlock, (npos-2)/3*3 + 2);
}

inline int checkEqual(VI& A, int i, int j, int k){
    return A[i] == A[k] && A[i] == A[j];
}

inline void solve(VVI& dp, VI& A, int i, int j, int s) {
    if (s <= j && s+3 > j) {
        s += 3;
    }

    if (s <= j || j <= i) {
        return ;
    }

    int plus = s < A.size() ? checkEqual(A, i, j, s) : 0;
    dp[A.size()][A.size()] = max(dp[A.size()][A.size()], dp[i][j] + plus);

    if (s+2 < A.size()) {
        dp[i][s+0] = max(dp[i][s+0], dp[i][j] + checkEqual(A, j, s+1, s+2));
        dp[i][s+1] = max(dp[i][s+1], dp[i][j] + checkEqual(A, j, s+0, s+2));
        dp[i][s+2] = max(dp[i][s+2], dp[i][j] + checkEqual(A, j, s+0, s+1));

        dp[j][s+0] = max(dp[j][s+0], dp[i][j] + checkEqual(A, i, s+1, s+2));
        dp[j][s+1] = max(dp[j][s+1], dp[i][j] + checkEqual(A, i, s+0, s+2));
        dp[j][s+2] = max(dp[j][s+2], dp[i][j] + checkEqual(A, i, s+0, s+1));

        dp[s+0][s+1] = max(dp[s+0][s+1], dp[i][j] + checkEqual(A, i, j, s+2));
        dp[s+0][s+2] = max(dp[s+0][s+2], dp[i][j] + checkEqual(A, i, j, s+1));
        dp[s+1][s+2] = max(dp[s+1][s+2], dp[i][j] + checkEqual(A, i, j, s+0));
    }
}

int main() {
    int N;
    cin >> N;

    VI A;
    int ans = 0;

    for (int i = 0; i <= N; ++i) {
        // pattern: 2, 3, 3 .... , 1
        int upper = 2 + (i > 0) - 2*(i == N);
        for (int j = 0; j < upper; ++j) {
            int v;
            cin >> v;
            A.push_back(v);
        }

        while (A.size() >= 3) {
            int aSize = A.size();

            if (A[aSize-1] == A[aSize-2] && A[aSize-1] == A[aSize-3]) {
                A.pop_back();
                A.pop_back();
                A.pop_back();
                ++ans;
            } else {
                break;
            }
        }
    }

    VVI dp(A.size()+1, VI(A.size()+1, -1));
    VI curPos(N+1, -1);
    VI nextPos(A.size() + 1);

    for (int p = A.size()-1; p >= 0; --p) {
        nextPos[p] = curPos[A[p]];
        curPos[A[p]] = p;
    }

    dp[0][1] = 0;

    for (int i= 0; i < A.size(); ++i) {
       for (int j = i+1; j < A.size(); ++j) {
            if (dp[i][j] == -1) {
                continue;
            }

            solve(dp, A, i, j, getBlockStart(j+1, j));

            // match i
            solve(dp, A, i, j, getBlockStart(nextPos[i], j));

            // match j
            solve(dp, A, i, j, getBlockStart(nextPos[j], j));
       }
    }

    if (!A.empty()) {
        cout << ans + dp[A.size()][A.size()] << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
