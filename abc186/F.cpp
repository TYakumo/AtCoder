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

template<class T>
class FenwickTree {
    vector <T> sum;
public:
    FenwickTree (int treeSize) {
        sum = move(vector<T>(treeSize+1));
    }

    void addVal(int idx, T val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    T getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        T ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    T queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};

int main() {
    int H;
    int W;
    int M;
    const int CG = 100;

    cin >> H >> W >> M;
    VI X(M);
    VI Y(M);
    VI MINX(W+CG, H+1);
    VI MINY(H+CG, W+1);

    VI YBLOCK(W+CG);
    VI XBLOCK(H+CG);

    for (int i = 0; i < M; ++i) {
        cin >> X[i] >> Y[i];

        MINX[Y[i]] = min(MINX[Y[i]], X[i]);
        MINY[X[i]] = min(MINY[X[i]], Y[i]);

        if (X[i] == 1) {
            YBLOCK[Y[i]] = 1;
        }

        if (Y[i] == 1) {
            XBLOCK[X[i]] = 1;
        }
    }

    long long ans = 1;
    FenwickTree<long long> ft(W+CG);
    VVI minus(H+CG);

    for (int y = 2; y <= W; ++y) {
        ft.addVal(y, 1);
    }

    int breaker = W+1;

    for (int y = 2; y <= W; ++y) {
        if (YBLOCK[y]) {
            breaker = y;
            break;
        }

        minus[MINX[y]].push_back(y);
        ans += MINX[y]-1;
    }

    for (int y = breaker; y <= W; ++y) {
        minus[1].push_back(y);
    }

    for (int i = 0; i < minus[1].size(); ++i) {
        ft.addVal(minus[1][i], -1);
    }

    for (int x = 2; x <= H; ++x) {
        if (XBLOCK[x]) {
            break;
        }

        for (int i = 0; i < minus[x].size(); ++i) {
            ft.addVal(minus[x][i], -1);
        }

        ans += MINY[x]-1;
        long long ycnt = ft.getVal(MINY[x]-1);
        ans -= ycnt;
    }

    cout << ans << endl;

    return 0;
}