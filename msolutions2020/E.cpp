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
int N;
VLL X;
VLL Y;
VLL P;
VLL ans;
VLL defaultMinDist;
VPILL PX;
VPILL PY;
int xcho;
int ycho;

const long long INF = 1000000000LL * 1000000000LL;

void solve(int now, int chosen) {
    if (now == N) {
        VLL minDist(defaultMinDist);

        long long res = 0;
        long long lastX = -INF;
        long long lastY = -INF;

        for (int i = 0; i < N; ++i) {
            // x axis
            if (xcho & (1 << PX[i].second)) {
                lastX = PX[i].first;
            }

            minDist[PX[i].second] = min(minDist[PX[i].second], PX[i].first-lastX);

            // y axis
            if (ycho & (1 << PY[i].second)) {
                lastY = PY[i].first;
            }

            minDist[PY[i].second] = min(minDist[PY[i].second], PY[i].first-lastY);
        }

        // backward
        lastX = INF;
        lastY = INF;

        for (int i = N-1; i >= 0; --i) {
            // x axis
            if (xcho & (1 << PX[i].second)) {
                lastX = PX[i].first;
            }

            minDist[PX[i].second] = min(minDist[PX[i].second], lastX-PX[i].first);

            // y axis
            if (ycho & (1 << PY[i].second)) {
                lastY = PY[i].first;
            }

            minDist[PY[i].second] = min(minDist[PY[i].second], lastY - PY[i].first);
        }

        for (int i = 0; i < N; ++i) {
            res += P[i] * minDist[i];
        }

        ans[chosen] = min(ans[chosen], res);
        return ;
    }

    solve(now+1, chosen);

    xcho |= (1<<now);
    solve(now+1, chosen+1);
    xcho &= ~(1<<now);

    ycho |= (1<<now);
    solve(now+1, chosen+1);
    ycho &= ~(1<<now);
}

int main() {
    cin >> N;

    X = VLL(N);
    Y = VLL(N);
    P = VLL(N);
    defaultMinDist = VLL(N, INF);

    PX = VPILL(N);
    PY = VPILL(N);

    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i] >> P[i];
        PX[i] = make_pair(X[i], i);
        PY[i] = make_pair(Y[i], i);
        defaultMinDist[i] = min(defaultMinDist[i], min(abs(X[i]), abs(Y[i])));
    }

    ans = VLL(N+1, INF);
    xcho = 0;
    ycho = 0;

    sort(PX.begin(), PX.end());
    sort(PY.begin(), PY.end());
    solve(0, 0);

    for (int k = 0; k <= N; ++k) {
        cout << ans[k] << endl;
    }

    return 0;
}