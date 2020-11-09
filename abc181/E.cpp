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

using VLL = vector <long long>;

long long calc(int now, VLL& H, VLL& sum) {
    if (now >= H.size()) {
        return 0;
    }

    return sum[now] = H[now] + calc(now+2, H, sum);
}

long long getSum(int f, int t, VLL& sum) {
    if (t < f) {
        return 0;
    }

    long long ret = -sum[f];

    if (f+1 < sum.size()) {
        ret += sum[f+1];
    }

    if (t+1 < sum.size()) {
        ret += sum[t+1];
    }

    if (t+2 < sum.size()) {
        ret -= sum[t+2];
    }

    return ret;
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    VLL H(N);
    VLL W(M);
    VLL sum(N);

    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }

    for (int i = 0; i < M; ++i) {
        cin >> W[i];
    }

    sort(H.begin(), H.end());
    calc(0, H, sum);
    calc(1, H, sum);

    const long long INF = 1000000000LL * 1000000000LL;
    long long ans = INF;

    for (int i = 0; i < M; ++i) {
        int low = 0;
        int up = H.size()-1;
        int insertPos = -1;
        long long res = 0;
        long long nowVal = W[i];

        while (low <= up) { // find nowVal >= H[i]
            int mid = (low+up) / 2;

            if (nowVal >= H[mid]) {
                insertPos = mid;
                low = mid+1;
            } else {
                up = mid-1;
            }
        }

        // 0 ~ insertPos, now, insertPos+1 ~ end
        if (insertPos == -1) {
            res += getSum(1, H.size()-1, sum);
            res += H[0] - nowVal;
        } else if (insertPos%2 == 0) {
            // now mapped with insertPos
            int mpos = insertPos-1;
            res += getSum(0, mpos, sum);
            res += getSum(insertPos+1, H.size()-1, sum);
            res += nowVal - H[insertPos];
        } else {
            // now mapped with insertPos+1
            res += getSum(0, insertPos, sum);
            res += getSum(insertPos+2, H.size()-1, sum);
            res += H[insertPos+1] - nowVal;
        }

        ans = min(ans, res);
    }

    cout << ans << endl;

    return 0;
}