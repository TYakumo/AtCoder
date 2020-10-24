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

using VLL = vector <long long>;
using VVLL = vector <VLL>;

using VI = vector <int>;
using VVI = vector <VI>;

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;
    VLL groupSum;

    UnionAndFind (int gSize) {
        groupSize = VI (gSize, 1);
        groupParent = VI (gSize, -1);
        groupSum = VLL (gSize, 0);
    }

    void setGroupSum(int n, long long val) {
        groupSum[n] = val;
    }

    long long getGroupSum(int n) {
        return groupSum[findGroup(n)];
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
        groupSum[y] += groupSum[x];
        groupParent[x] = y;
    }
};


int main() {
    int N;
    int M;

    cin >> N >> M;

    VLL A(N);
    VLL B(N);
    UnionAndFind uaf(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> B[i];
        uaf.setGroupSum(i, B[i]-A[i]);
    }

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;
        uaf.unionGroup(f-1, t-1);
    }

    bool ok = true;
    for (int i = 0; i < N; ++i) {
        if (uaf.getGroupSum(i) != 0) {
            ok = false;
            break;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}