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
    long long N;
    cin >> N;

    long long sq = sqrt((double)N);
    vector <int> pows;

    for (int v = 2; v <= sq; ++v) {
        int cnt = 0;

        while (N % v == 0) {
            ++cnt;
            N /= v;
        }

        if (cnt) {
            pows.push_back(cnt);
        }
    }

    if (N != 1) { // prime
        pows.push_back(1);
    }

    int ans = 0;
    for (int i = 0; i < pows.size(); ++i) {
        // x(x+1)/2 <= pows[i]
        // x(x+1) <= 2*pows[i]
        int low = 0;
        int up = 2*pows[i];
        int res = 0;

        while (low <= up) {
            int mid = (low+up) / 2;

            if (mid*(mid+1) <= 2*pows[i]) {
                res = mid;
                low = mid+1;
            } else {
                up = mid-1;
            }
        }

        ans += res;
    }

    cout << ans << endl;

    return 0;
}