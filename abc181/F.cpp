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

using VD = vector <double>;

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

    VD x(N);
    VD y(N);

    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }

    double ans = 0;
    double low = 0;
    double up = 100;

    for (int it = 0; it < 1000; ++it) {
        double mid = (low+up) / 2;
        UnionAndFind ut(N+2);

        for (int i = 0; i < N; ++i) {
            if (y[i] - 2*mid <= -100.0) {
                ut.unionGroup(0, i+2);
            }

            if (y[i] + 2*mid >= 100.0) {
                ut.unionGroup(1, i+2);
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                double dx = x[i]-x[j];
                double dy = y[i]-y[j];

                if (sqrt(dx*dx+dy*dy) <= 2*mid) {
                    ut.unionGroup(i+2, j+2);
                }
            }
        }

        if (ut.findGroup(0) == ut.findGroup(1)) { // failed
            up = mid;
        } else {
            low = mid;
            ans = mid;
        }
    }

    cout << setprecision(15) << fixed << ans << endl;
    return 0;
}