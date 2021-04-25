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

const long long MOD = 1000000000+7;

struct GCDInfo {
    long long x;
    long long y;
    long long g;
    GCDInfo(long long px, long long py, long long pg) : x(px), y(py), g(pg) {
    }
};

GCDInfo gcd(long long a, long long b) {
    if (b == 0) {
        return GCDInfo(1, 0, a);
    }

    // ax+by = g
    // bx'+(a-a/b*b)y' = g
    GCDInfo v = gcd(b, a%b);
    return GCDInfo(v.y%(b/v.g), (v.x-(a/b)*v.y)%(a/v.g), v.g);
}

// Get a * x mod p = 1
long long findInv(long long a, long long p) {
    return gcd(a, p).x;
}

VVLL matMul(VVLL A, VVLL B) {
    int N = A.size();
    int M = B[0].size();
    VVLL ret(N, VLL(M));

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ret[i][j] += A[i][k] * B[k][j];
                ret[i][j] %= MOD;
            }
        }
    }

    return ret;
}

VVLL matPow(VVLL mat, long long p) {
    int N = mat.size();
    if (p == 0) {
        VVLL iden(N, VLL(N));
        for (int i = 0; i < N; ++i) {
            iden[i][i] = 1;
        }
        return iden;
    }

    if (p == 1) {
        return mat;
    }

    VVLL half = matPow(mat, p/2);
    VVLL ret = matMul(half, half);

    if (p%2) {
        ret = matMul(mat, ret);
    }

    return ret;
}

int main() {
    int N;
    int M;
    int K;
    cin >> N >> M >> K;

    VVLL A(N, VLL(1));
    VVLL mat(N, VLL(N));
    VLL cnt(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i][0];
    }

    for (int i = 0; i < M; ++i) {
        int X;
        int Y;
        cin >> X >> Y;
        --X;
        --Y;

        ++cnt[X];
        ++cnt[Y];

        mat[Y][X] += findInv(2*M, MOD);
        mat[Y][Y] += findInv(2*M, MOD);
        mat[X][X] += findInv(2*M, MOD);
        mat[X][Y] += findInv(2*M, MOD);

        mat[X][Y] %= MOD;
        mat[X][X] %= MOD;
        mat[Y][Y] %= MOD;
        mat[Y][X] %= MOD;
    }

    for (int i = 0; i < N; ++i) {
        long long prob = M-cnt[i];

        if (prob > 0) {
            mat[i][i] += prob*findInv(M, MOD);
            mat[i][i] %= MOD;
        }
    }

    VVLL p = matPow(mat, K);
    VVLL ans = matMul(p, A);

    for (int i = 0; i < ans.size(); ++i) {
        cout << (ans[i][0]+MOD)%MOD << endl;
    }

    return 0;
}