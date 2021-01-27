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
using VLL = vector <long long>;
using VVLL = vector <VLL>;

VVLL multiply(const VVLL& mat1, const VVLL& mat2) {
    VVLL ret(mat1.size(), VLL(mat2[0].size()));

    for (int i = 0; i < mat1.size(); ++i) {
        for (int j = 0; j < mat2[0].size(); ++j) {
            for (int k = 0; k < mat2.size(); ++k) {
                ret[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return ret;
}

int main() {
    int N;
    int M;
    int Q;

    cin >> N;
    VI X(N);
    VI Y(N);

    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    cin >> M;
    VVI OP(M);
    for (int i = 0; i < M; ++i) {
        int op;
        int v;
        cin >> op;

        if (op > 2) {
            cin >> v;
            OP[i] = {op, v};
        } else {
            OP[i] = {op};
        }
    }

    cin >> Q;
    VVI query(Q);
    VVLL ans(Q);
    for (int i = 0; i < Q; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --b;
        query[i] = {a, b, i};
    }

    sort(query.begin(), query.end());
    int idx = 0;
    VVLL mat(2);
    VVLL cmat(2);
    mat[0] = {1, 0};
    mat[1] = {0, 1};
    cmat[0] = {0};
    cmat[1] = {0};

    for (int i = 0; i <= M; ++i) {
        while (idx < query.size() && query[idx][0] == i) {
            int pidx = query[idx][1];
            int qidx = query[idx][2];
            long long ax = X[pidx];
            long long ay = Y[pidx];

            long long nx = mat[0][0] * ax + mat[0][1] * ay + cmat[0][0];
            long long ny = mat[1][0] * ax + mat[1][1] * ay + cmat[1][0];

            ans[qidx] = {nx, ny};
            ++idx;
        }

        if (i == M) {
            break;
        }

        if (OP[i][0] == 1) {
            VVLL nmat(2);
            nmat[0] = {0, 1};
            nmat[1] = {-1, 0};
            mat = multiply(nmat, mat);
            cmat = multiply(nmat, cmat);
        } else if (OP[i][0] == 2) {
            VVLL nmat(2);
            nmat[0] = {0, -1};
            nmat[1] = {1, 0};
            mat = multiply(nmat, mat);
            cmat = multiply(nmat, cmat);
        } else if (OP[i][0] == 3) {
            VVLL nmat(2);
            nmat[0] = {-1, 0};
            nmat[1] = {0, 1};
            mat = multiply(nmat, mat);
            cmat = multiply(nmat, cmat);
            cmat[0][0] += OP[i][1]*2;
        } else if (OP[i][0] == 4) {
            VVLL nmat(2);
            nmat[0] = {1, 0};
            nmat[1] = {0, -1};
            mat = multiply(nmat, mat);
            cmat = multiply(nmat, cmat);
            cmat[1][0] += OP[i][1]*2;
        }
    }

    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}