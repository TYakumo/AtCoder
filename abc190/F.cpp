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
#include <queue>
using namespace std;

using VI = vector <int>;
using DI = deque <int>;

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
    int N;
    cin >> N;
    DI A(N);
    long long ans = 0;
    FenwickTree <int> ft(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        ++A[i];
        ans += ft.queryRange(A[i]+1, N);
        ft.addVal(A[i], 1);
    }

    for (int i = 0; i < N; ++i) {
        cout << ans << endl;
        // rotation
        int now = A.front();
        A.pop_front();
        A.push_back(now);
        ans -= now-1;
        ans += (N-now);
    }

    return 0;
}