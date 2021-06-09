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

const long long MOD = 998244353;

void solve(int idx, int N, int now, int next, VVLL& trans) {
    if (idx == N) {
        ++trans[now][next];
        return ;
    }

    int flag = 1<<idx;
    int nflag = 1<<(idx+1);

    solve(idx+1, N, now, next, trans);
    if ((now&flag)== 0) {
        solve(idx+1, N, now, next|flag, trans);
    }

    if (idx+2 <= N) {
        if ((now&flag) == 0 && (now&nflag) == 0) {
            solve(idx+2, N, now, next, trans);
        }
    }
}

VVLL matMul(const VVLL& a, const VVLL& b) {
    int N = a.size();
    int K = a[0].size();
    int M = b[0].size();
    VVLL ret(N, VLL(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < K; ++k) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] %= MOD;
            }
        }
    }

    return ret;
}

VVLL matPow(VVLL base, long long p) {
    int N = base.size();
    if (p == 0) {
        VVLL iden(N, VLL(N));
        for (int i = 0; i < N; ++i) {
            iden[i][i] = 1;
        }
        return iden;
    }

    if (p == 1) {
        return base;
    }

    VVLL sqMat = matPow(base, p/2);
    VVLL ret = matMul(sqMat, sqMat);

    if (p%2 == 1) {
        ret = matMul(ret, base);
    }

    return ret;
}

int main() {
    int H;
    long long W;
    cin >> H >> W;

    int UPPER = 1<<H;
    VVLL trans(UPPER, VLL(UPPER));
    for (int st = 0; st < UPPER; ++st) {
        solve(0, H, st, 0, trans);
    }

    VVLL state(UPPER, VLL(1));
    state[0][0] = 1;

    state = matMul(matPow(trans, W), state);
    cout << state[0][0] << endl;

    return 0;
}