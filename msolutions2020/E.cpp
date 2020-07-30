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
using VPILL = vector < pair<long long, int> >;

int mypow(int n, int p) {
    if (p == 0) {
        return 1;
    }

    int half = mypow(n, p/2);
    return half * half *  (1 + (p&1) * (n-1));
}

int main() {
    int N;
    cin >> N;

    VLL X(N);
    VLL Y(N);
    VLL P(N);

    VPILL PX(N);
    VPILL PY(N);

    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i] >> P[i];
        PX[i] = make_pair(X[i], i);
        PY[i] = make_pair(Y[i], i);
    }

    int superset = mypow(3, N);
    const long long INF = 1000000000LL * 1000000000LL;
    VLL ans(N+1, INF);

    sort(PX.begin(), PX.end());
    sort(PY.begin(), PY.end());

    for (int sub = 0; sub < superset; ++sub) {
        vector <bool> xcho(N);
        vector <bool> ycho(N);

        int val = sub;
        int cho = 0;
        long long res = 0;

        for (int i = 0; i < N; ++i) {
            if (val % 3 == 1) {
                ++cho;
                xcho[i] = true;
            } else if (val % 3 == 2) {
                ++cho;
                ycho[i] = true;
            }

            val /= 3;
        }

        VLL minDist(N, INF);

        // forward
        long long lastX = -INF;
        long long lastY = -INF;

        for (int i = 0; i < N; ++i) {
            // default
            minDist[i] = min(minDist[i], min(abs(X[i]), abs(Y[i])));

            // x axis
            if (xcho[PX[i].second]) {
                lastX = PX[i].first;
            }

            minDist[PX[i].second] = min(minDist[PX[i].second], PX[i].first-lastX);

            // y axis
            if (ycho[PY[i].second]) {
                lastY = PY[i].first;
            }

            minDist[PY[i].second] = min(minDist[PY[i].second], PY[i].first-lastY);
        }

        // backward
        lastX = INF;
        lastY = INF;

        for (int i = N-1; i >= 0; --i) {
            // x axis
            if (xcho[PX[i].second]) {
                lastX = PX[i].first;
            }

            minDist[PX[i].second] = min(minDist[PX[i].second], lastX-PX[i].first);

            // y axis
            if (ycho[PY[i].second]) {
                lastY = PY[i].first;
            }

            minDist[PY[i].second] = min(minDist[PY[i].second], lastY - PY[i].first);
        }

        for (int i = 0; i < N; ++i) {
            res += P[i] * minDist[i];
        }

        ans[cho] = min(ans[cho], res);
    }

    for (int k = 0; k <= N; ++k) {
        cout << ans[k] << endl;
    }

    return 0;
}