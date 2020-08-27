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
using VS = vector < set<int> >;

inline int getNextIdx(VVI& vs, int val, int npos) {
    auto iter = upper_bound(vs[val].begin(), vs[val].end(), npos);

    if (iter == vs[val].end()) {
        return -1;
    }

    return *iter;
}

inline int getBlockStart(VVI& vs, int val, int npos) {
    int pos = getNextIdx(vs, val, npos);
    int nextBlock = (npos+1-2)/3 * 3 + 2;
    return pos < 0 ? nextBlock : (pos-2)/3*3 + 2;
}

int checkEqual(VI& A, int i, int j, int k){
    return A[i] == A[k] && A[i] == A[j];
}

int checkValid(VI& A, int i, int j, int l1, int l2, int l3){
    return (i > l1 || A[i] != A[l1])
        && (i > l2 || A[i] != A[l2])
        && (i > l3 || A[i] != A[l3])
        && (j > l1 || A[j] != A[l1])
        && (j > l2 || A[j] != A[l2])
        && (j > l3 || A[j] != A[l3]);
}

void solve(VVI& dp, VI& A, int i, int j, int s) {
    if (s <= j && s+3 > j) {
        s += 3;
    }

    dp[A.size()][A.size()] = max(dp[A.size()][A.size()], dp[i][j]);

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
    } else if (s < A.size()) {
        dp[A.size()][A.size()] = max(dp[A.size()][A.size()], dp[i][j] + checkEqual(A, i, j, s));
    }
}

int main() {
    int N;
    cin >> N;

    VI A;
    VVI vs(N+1);
    int ans = 0;

    for (int i = 0; i <= N; ++i) {
        int upper = 2 + (i > 0) - 2*(i == N);
        for (int j = 0; j < upper; ++j) {
            int v;
            cin >> v;
            A.push_back(v);
        }

        while (A.size() >= 3) {
            int aSize = A.size();
            // cout << "GO " << aSize << endl;

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

    // cout << "FINAL " << A.size() << " " << ans << endl;
    for (int i = 0; i < A.size(); ++i) {
        vs[A[i]].push_back(i);
    }

    VVI dp(A.size()+1, VI(A.size()+1, -1));
    VI nextPos(A.size());

    dp[0][1] = 0;

    for (int i= 0; i < A.size(); ++i) {
       for (int j = i+1; j < A.size(); ++j) {
            if (dp[i][j] == -1) {
                continue;
            }

            solve(dp, A, i, j, (j+1-2)/3*3+2);

            // match i
            solve(dp, A, i, j, getBlockStart(vs, A[i], j));

            // match j
            solve(dp, A, i, j, getBlockStart(vs, A[j], j));
       }
    }

    if (!A.empty()) {
        cout << ans + dp[A.size()][A.size()] << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
