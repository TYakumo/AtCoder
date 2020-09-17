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

using PLL = pair<long long, long long>;
using VPLL = vector <PLL>;

bool cmp1(const PLL& a, const PLL& b) {
    return (a.first + a.second) < (b.first + b.second);
}

bool cmp2(const PLL& a, const PLL& b) {
    return (a.first - a.second) < (b.first - b.second);
}


int main() {
    int N;
    cin >> N;

    VPLL pnts(N);
    for (int i = 0; i < N; ++i) {
        cin >> pnts[i].first >> pnts[i].second;
    }

    long long ans = 0;

    // case 1 abs((xi+yi) - (xj+yj))
    sort(pnts.begin(), pnts.end(), cmp1);

    for (int i = 0; i < pnts.size(); ++i) {
        if (i != 0) {
            ans = max(ans, abs(pnts[i].first- pnts[0].first) + abs(pnts[i].second- pnts[0].second));
        }

        if (i != pnts.size()-1) {
            ans = max(ans, abs(pnts[i].first- pnts.back().first) + abs(pnts[i].second- pnts.back().second));
        }
    }

    // case 2 abs((xi-yi) - (xj-yj))
    sort(pnts.begin(), pnts.end(), cmp2);

    for (int i = 0; i < pnts.size(); ++i) {
        if (i != 0) {
            ans = max(ans, abs(pnts[i].first- pnts[0].first) + abs(pnts[i].second- pnts[0].second));
        }

        if (i != pnts.size()-1) {
            ans = max(ans, abs(pnts[i].first- pnts.back().first) + abs(pnts[i].second- pnts.back().second));
        }
    }

    cout << ans << endl;

    return 0;
}