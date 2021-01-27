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

int main() {
    int N;
    cin >> N;

    VVI A(N);
    VI ok(N);
    for (int i = 0; i < N; ++i) {
        int v;
        cin >> v;

        VI VA = {v, i};
        A[i] = VA;
    }

    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());
    int ans = 0;
    UnionAndFind ut(N);

    for (int i = 0; i < A.size(); ++i) {
        int now = A[i][1];

        ok[now] = 1;

        if (now-1 >= 0 && ok[now-1]) {
            ut.unionGroup(now-1, now);
        }

        if (now+1 < N && ok[now+1]) {
            ut.unionGroup(now+1, now);
        }

        int gs = ut.groupSize[ut.findGroup(now)];
        ans = max(ans, gs*A[i][0]);
    }

    cout << ans << endl;

    return 0;
}