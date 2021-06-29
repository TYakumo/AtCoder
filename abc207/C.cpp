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
using VD = vector <double>;
using VVD = vector <VD>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    cin >> N;

    const double eps = 1e-10;
    VVI line(N);
    VVI pnt;

    for (int i = 0; i < N; ++i) {
        int t;
        int l;
        int r;
        cin >> t >> l >> r;
        if (t == 1) {
            pnt.push_back({l, 0, 0});
            pnt.push_back({r, 1, 1});
        } else if (t == 2) {
            pnt.push_back({l, 0, 0});
            pnt.push_back({r, -1, 1});
        } else if (t == 3) {
            pnt.push_back({l, 2, 0});
            pnt.push_back({r, 1, 1});
        } else if (t == 4) {
            pnt.push_back({l, 2, 0});
            pnt.push_back({r, -1, 1});
        }

        line[i] = {t, l, r};
    }

    int ans = 0;
    sort(pnt.begin(), pnt.end());
    int pntSize = 0;

    for (int i = 0; i < pnt.size(); ++i) {
        if (pnt[i][2] == 0) {
            ans += pntSize;
            ++pntSize;
        } else {
            --pntSize;
        }
    }

    cout << ans << endl;

    return 0;
}