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
    int N;
    scanf("%d", &N);

    vector <int> arr(N);
    const long long INF = 1000000000LL * 100010;
    vector<vector <long long>> evenBest(N, vector<long long>(2, -INF));

    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }

    evenBest[N-2][1] = arr[N-2];
    evenBest[N-2][0] = arr[N-1];

    for (int i = N-4; i >= 0; i -= 2) {
        evenBest[i][1] = max(evenBest[i+2][0], evenBest[i+2][1]) + arr[i];
        evenBest[i][0] = evenBest[i+2][0] + arr[i+1];
    }

    if (N%2 == 0) {
        cout << max(evenBest[0][0], evenBest[0][1]) << endl;
    } else {
        long long ans = -INF;
        long long curSum = 0;

        for (int i = 0; i < N; i += 2) {
            // give up i
            if (i+1 < N) {
                long long best = max(evenBest[i+1][0], evenBest[i+1][1]);
                ans = max(ans, curSum + best);
            }

            curSum += arr[i];
        }

        ans = max(ans, curSum-arr[N-1]);
        ans = max(ans, curSum-arr[0]);

        cout << ans << endl;
    }

    return 0;
}