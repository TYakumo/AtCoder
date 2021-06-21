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
    VI A(N);
    const int MAXV = 200020;
    UnionAndFind ut(MAXV);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int hlen = N/2;
    int ans = 0;

    for (int i = 0; i < hlen; ++i) {
        if (ut.findGroup(A[i]) != ut.findGroup(A[N-1-i])) {
            ++ans;
            ut.unionGroup(A[i], A[N-1-i]);
        }
    }

    cout << ans << endl;

    return 0;
}