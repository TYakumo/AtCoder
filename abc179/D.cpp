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
const long long MOD = 998244353;

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
            sum[idx] %= MOD;
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
            ret %= MOD;
            idx -= (idx & (-idx));
        }

        return ret;
    }

    T queryRange(int a, int b) {
        return ((getVal(b) - getVal(a-1))%MOD + MOD ) % MOD;
    }
};

int main() {
    int N;
    int K;

    cin >> N >> K;
    VVI V(N, VI(2));
    FenwickTree <long long> ft(N+1);

    for (int i = 0; i < K; ++i) {
        cin >> V[i][0] >> V[i][1];
    }

    ft.addVal(1, 1);

    for (int p = 2; p <= N; ++p) {
        long long res = 0;

        for (int k = 0; k < K; ++k){
            int start = max(1, p-V[k][1]);
            int to = p-V[k][0];

            if (to >= start) {
                res += ft.queryRange(start, to);
                res %= MOD;
            }
        }

        ft.addVal(p, res);
    }

    cout << ft.queryRange(N, N) << endl;

    return 0;
}