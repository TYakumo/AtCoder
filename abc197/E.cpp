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
using VVLL = vector <VLL>;

int main() {
    int N;
    cin >> N;

    VVLL balls;

    for (int i = 0; i < N; ++i) {
        long long X;
        long long C;
        cin >> X >> C;
        balls.push_back({C, X});
    }

    sort(balls.begin(), balls.end());

    const long long INF = 1000000000LL * 1000000000LL;
    VLL coor = {0, 0};
    VLL dp1(2);

    for (int i = 0; i < N;) {
        VLL dp2(2, INF);
        long long minX = INF;
        long long maxX = -INF;

        int end = i;
        for (int j = i; j < N; ++j) {
            if (balls[i][0] == balls[j][0]) {
                minX = min(minX, balls[j][1]);
                maxX = max(maxX, balls[j][1]);
                ++end;
            } else {
                break;
            }
        }

        // from previous minX to new maxX
        if (coor[0] >= minX && coor[0] <= maxX) {
            dp2[1] = min(dp2[1], dp1[0] + (coor[0]-minX) + (maxX-minX));
        } else if (coor[0] >= maxX) {
            dp2[1] = min(dp2[1], dp1[0] + (coor[0]-minX) + (maxX-minX));
        } else {
            dp2[1] = min(dp2[1], dp1[0] + (maxX-coor[0]));
        }

        // from previous maxX to new maxX
        if (coor[1] >= minX && coor[1] <= maxX) {
            dp2[1] = min(dp2[1], dp1[1] + (coor[1]-minX) + (maxX-minX));
        } else if (coor[1] >= maxX) {
            dp2[1] = min(dp2[1], dp1[1] + (coor[1]-minX) + (maxX-minX));
        } else {
            dp2[1] = min(dp2[1], dp1[1] + (maxX-coor[1]));
        }

        // from previous minX to new minX
        if (coor[0] >= minX && coor[0] <= maxX) {
            dp2[0] = min(dp2[0], dp1[0] + (maxX - coor[0]) + (maxX-minX));
        } else if (coor[0] >= maxX) {
            dp2[0] = min(dp2[0], dp1[0] + (coor[0]-minX));
        } else {
            dp2[0] = min(dp2[0], dp1[0] + (maxX-coor[0]) + (maxX-minX));
        }

        // from previous maxX to new minX
        if (coor[1] >= minX && coor[1] <= maxX) {
            dp2[0] = min(dp2[0], dp1[1] + (maxX - coor[1]) + (maxX-minX));
        } else if (coor[1] >= maxX) {
            dp2[0] = min(dp2[0], dp1[1] + (coor[1]-minX));
        } else {
            dp2[0] = min(dp2[0], dp1[1] + (maxX-coor[1]) + (maxX-minX));
        }

        coor = {minX, maxX};
        dp1 = dp2;
        i = end;
    }

    cout << min(dp1[0]+abs(coor[0]), dp1[1]+abs(coor[1])) << endl;
    return 0;
}