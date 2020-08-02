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
    int K;

    cin >> N >> K;

    vector <int> A(N);
    double low = 1;
    double up = 1;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        up = max(up, (double)A[i]);
    }

    double ans = 1e+20;

    for (int i = 0; i < 100; ++i) {
        double mid = (low+up) / 2;
        long long cutNeeded = 0;

        for (int i = 0; i < N; ++i) {
            long long needed = (long long) ceil((double)A[i] / mid);
            cutNeeded += (needed-1);
        }

        if (cutNeeded <= K) { // [low, mid]
            up = mid;
            ans = mid;
        } else { // [mid, up]
            low = mid;
        }
    }

    cout << (long long) ceil(ans) << endl;

    return 0;
}