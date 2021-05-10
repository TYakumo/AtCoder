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
        if (b < a) {
            return 0;
        }

        return getVal(b) - getVal(a-1);
    }
};

int main() {
    int N;
    long long K;
    cin >> N >> K;

    vector <FenwickTree<long long>> ft;
    ft.push_back(FenwickTree<long long>(N+10));
    ft.push_back(FenwickTree<long long>(N*2+10));
    ft.push_back(FenwickTree<long long>(N*3+10));

    for (int i = 1; i <= N; ++i) {
        ft[0].addVal(i, 1);
    }

    for (int i = 1; i < 3; ++i) {
        // dp[i][s] = sigma j = 1...N dp[i-1][s-j]
        int upper = (i+1)*N;
        int preupper = i*N;

        for (int s = i+1; s <= upper; ++s) {
            int t = min(s-1, preupper);
            int f = max(i, s-N);
            ft[i].addVal(s, ft[i-1].queryRange(f, t));
        }
    }

    int low = 3;
    int up = 3*N;
    int smax = 2;

    while (low <= up) {
        int mid = (low+up) / 2;
        long long comb = ft[2].queryRange(3, mid);

        if (comb < K) {
            low = mid+1;
            smax = mid;
        } else {
            up = mid-1;
        }
    }

    K -= ft[2].queryRange(3, smax);
    --K;
    int target = smax+1;
    VLL ans(3, 1);
    long long comb = 0;

    for (int v = 1; v <= N && v <= target-2; ++v) {
        int remain = target-v;
        long long diff = min(remain-1, N) - max(0, remain-N-1);
        long long newComb = remain <= 2*N && diff > 0 ? comb + diff : comb;

        if (newComb > K || v == N || v == target-2) {
            ans[0] = v;
            K -= comb;
            break;
        }

        comb = newComb;
    }

    int remain = target-ans[0];
    int start = max(1, remain-N);
    ans[1] = min(start + K, (long long)N);
    ans[2] = remain-ans[1];

    cout << ans[0] << " " << ans[1] << " " << ans[2] << endl;

    return 0;
}