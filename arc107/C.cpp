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
const long long MOD = 998244353;
VLL fact;

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;

    UnionAndFind (int gSize) {
        groupSize = vector<int> (gSize, 1);
        groupParent = vector<int> (gSize, -1);
    }

    int findGroup(int n) {
        if (groupParent[n] == -1) {
            return n;
        }
        return groupParent[n] = findGroup(groupParent[n]);
    }

    void unionGroup(int x, int y) {
        y = findGroup(y);
        x = findGroup(x);

        if (x == y) {
            return ;
        }

        if (groupSize[x] > groupSize[y]) {
            swap(x, y);
        }

        groupSize[y] += groupSize[x];
        groupParent[x] = y;
    }
};

long long calcComb(VVI& arr, int K) {
    int N = arr.size();

    UnionAndFind ut(N);

    long long ret = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            bool ok = true;
            for (int a = 0; a < N; ++a) {
                if (arr[a][i] + arr[a][j] > K) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                ut.unionGroup(i, j);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (ut.findGroup(i) == i) {
            int gSize = ut.groupSize[ut.findGroup(i)];
            ret = (ret * fact[gSize]) % MOD;
        }
    }

    return ret;
}

void transpose(VVI& arr) {
    int N = arr.size();

    VVI tmp = arr;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[j][i] = arr[i][j];
        }
    }

    arr = tmp;
}

int main() {
    int N;
    int K;

    cin >> N >> K;

    fact = VLL(N+1);
    fact[0] = 1;

    for (int i = 1; i <= N; ++i) {
        fact[i] = fact[i-1]*i % MOD;
    }

    VVI arr(N, VI(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> arr[i][j];
        }
    }

    long long ans = calcComb(arr, K);
    transpose(arr);
    long long res = calcComb(arr, K);

    ans = (ans * res) % MOD;
    cout << ans << endl;

    return 0;
}