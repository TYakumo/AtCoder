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

int main() {
    int H;
    int W;
    int M;
    cin >> H >> W >> M;

    unordered_map <int, int> rowCnt;
    unordered_map <int, int> colCnt;
    unordered_map <long long, int> cell;
    vector <int> rv;
    vector <int> cv;
    vector <int> mrv;
    vector <int> mcv;

    int maxRow = 0;
    int maxCol = 0;
    const long long OFFSET = 10000000LL;

    for (int i = 0; i < M; ++i) {
        int r;
        int c;
        cin >> r >> c;
        maxRow = max(maxRow, ++rowCnt[r]);
        maxCol = max(maxCol, ++colCnt[c]);
        rv.push_back(r);
        cv.push_back(c);
        cell[r * OFFSET + c] = 1;
    }

    int ans = 0;
    sort(rv.begin(), rv.end());
    sort(cv.begin(), cv.end());

    for (int ri = 0; ri < rv.size(); ++ri) {
        if (ri && rv[ri] == rv[ri-1]) {
            continue;
        }
        if (rowCnt[rv[ri]] == maxRow) {
            mrv.push_back(rv[ri]);
        }
    }

    for (int ci = 0; ci < cv.size(); ++ci) {
        if (ci && cv[ci] == cv[ci-1]) {
            continue;
        }
        if (colCnt[cv[ci]] == maxCol) {
            mcv.push_back(cv[ci]);
        }
    }

    long long comb = (long long) mrv.size() * mcv.size();

    if (comb > M) {
        // pigeon hole
        ans = maxRow + maxCol;
    } else {
        for (int ri = 0; ri < mrv.size(); ++ri) {
            for (int ci = 0; ci < mcv.size(); ++ci) {
                int r = mrv[ri];
                int c = mcv[ci];

                int sum = rowCnt[r] + colCnt[c] - cell[r*OFFSET + c];
                ans = max(ans, sum);
            }
        }
    }


    cout << ans << endl;

    return 0;
}