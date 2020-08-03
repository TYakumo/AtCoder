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

using VI = vector <int> ;
using VVI = vector <VI> ;
using VVVI = vector <VVI> ;

class FenwickTree {
    VI sum;
public:
    FenwickTree (int treeSize) {
        sum = move(VI(treeSize+1));
    }

    void addVal(int idx, int val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        int ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    int queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};

int main() {
    int N;
    int Q;
    cin >> N >> Q;

    VI c(N);
    VI idx(N);
    VVI colorVec(N);
    FenwickTree ft(N+1);

    for (int i = 0; i < N; ++i) {
        cin >> c[i];
        colorVec[--c[i]].push_back(i);
    }

    // sort all colors
    for (int i = 0; i < N; ++i) {
        sort(colorVec[i].begin(), colorVec[i].end());

        if (colorVec[i].size()) {
            ft.addVal(colorVec[i][0]+1, 1);
            ++idx[i];
        }
    }

    VVVI query(N);
    VI ans(Q);

    for (int q = 0; q < Q; ++q) {
        int l;
        int r;
        cin >> l >> r;
        query[l-1].push_back({r, q});
    }

    // enumerate coordinate
    for (int i = 0; i < N; ++i) {

        if (i) { // remove previous cell
            int color = c[i-1];
            ft.addVal(i, -1);

            if (idx[color] < colorVec[color].size()) {
                ft.addVal(colorVec[color][idx[color]]+1, 1);
                ++idx[color];
            }
        }

        for (int q = 0; q < query[i].size(); ++q) {
            ans[query[i][q][1]] = ft.queryRange(i+1, query[i][q][0]);
        }
    }

    for (int i = 0; i < Q; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}