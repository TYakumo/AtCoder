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

using UMII = unordered_map <int, int> ;

vector <int> getRange(vector<int>& pnts, UMII& lCnt, UMII& confirmedCnt, int upperBound) {
    const int UPPER = 1000000001;
    int startVal = UPPER;
    int endVal = 0;

    int lcnt = 0;
    int confirmed = 0;

    for (int i = 0; i < pnts.size(); ++i) {
        if (i && pnts[i] == pnts[i-1]) {
            continue;
        }

        lcnt += lCnt[pnts[i]];

        if (lcnt >= upperBound && confirmed < upperBound) {
            startVal = min(startVal, pnts[i]);
            endVal = max(endVal, pnts[i]);
        }

        confirmed += confirmedCnt[pnts[i]];
    }

    return {startVal, endVal};
}

int main() {
    int N;
    cin >> N;
    vector < int > pnts;

    int factor = N%2 == 0 ? 2 : 1;
    UMII lCnt;
    UMII confirmedCnt;

    for (int i = 0; i < N; ++i) {
        int A;
        int B;
        cin >> A >> B;

        pnts.push_back(A);
        pnts.push_back(B);

        ++lCnt[A];
        ++confirmedCnt[B];
    }

    int startVal = 1000000001;
    int endVal = 0;
    int upperBound = (N+1)/2;

    sort(pnts.begin(), pnts.end());
    vector <int> res = getRange(pnts, lCnt, confirmedCnt, upperBound);

    if (N%2 == 0) {
        vector <int> res2 = getRange(pnts, lCnt, confirmedCnt, upperBound+1);
        cout << res[1]+res2[1] - res[0] - res2[0] + 1 << endl;
    } else {
        cout << res[1] - res[0] + 1 << endl;
    }

    return 0;
}