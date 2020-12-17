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

template<class T>
class FenwickTree {
    vector <T> sum;
public:
    FenwickTree (int treeSize) {
        sum = move(vector<T>(treeSize+1));
    }

    void addVal(int idx, T val) {
        while (idx < sum.size()) {
            sum[idx] ^= val;
            idx += (idx & (-idx));
        }
    }

    T getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        T ret = 0;

        while (idx) {
            ret ^= sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    T queryRange(int a, int b) {
        return getVal(b) ^ getVal(a-1);
    }
};

int main() {
    int N;
    int Q;
    cin >> N >> Q;

    FenwickTree<int> ft(N);

    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        ft.addVal(i+1, val);
    }

    for (int q = 0; q < Q; ++q) {
        int T;
        int X;
        int Y;
        cin >> T >> X >> Y;

        if (T==1) {
            ft.addVal(X, Y);
        } else {
            cout << ft.queryRange(X, Y) << endl;
        }
    }

    return 0;
}