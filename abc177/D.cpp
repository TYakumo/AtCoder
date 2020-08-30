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
using VVI = vector < VI >;


class UnionAndFind {
    public:
    VI groupSize;
    VI groupParent;

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
    int M;
    cin >> N >> M;

    UnionAndFind group(N);

    for (int i = 0; i < M; ++i) {
        int f;
        int t;
        cin >> f >> t;

        --f;
        --t;
        group.unionGroup(f, t);
    }

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        ans = max(ans, group.groupSize[i]);
    }

    cout << ans << endl;
    return 0;
}