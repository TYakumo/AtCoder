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
using VI = vector <int>;

long long f(const VLL& A, const VI& T, long long v) {
    long long ret = v;

    for (int i = 0; i < T.size(); ++i) {
        if (T[i] == 1) {
            ret += A[i];
        } else if (T[i] == 2) {
            ret = max(ret, A[i]);
        } else {
            ret = min(ret, A[i]);
        }
    }

    return ret;
}

int main() {
    int N;
    cin >> N;

    VLL A(N);
    VI T(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> T[i];
    }

    int Q;
    cin >> Q;

    const long long INF = 1000000010LL * 200000;
    long long lower = -INF;
    long long upper = INF;
    long long lowVal = f(A, T, lower);
    long long upVal = f(A, T, upper);

    long long low = -INF;
    long long up = INF;

    while (low <= up) {
        long long mid = (low+up) / 2;
        long long nowVal = f(A, T, mid);

        if (lowVal == nowVal) {
            lowVal = nowVal;
            lower = mid;
            low = mid+1;
        } else {
            up = mid-1;
        }
    }

    low = -INF;
    up = INF;
    while (low <= up) {
        long long mid = (low+up) / 2;
        long long nowVal = f(A, T, mid);

        if (nowVal == upVal) {
            upVal = nowVal;
            upper = mid;
            up = mid-1;
        } else {
            low = mid+1;
        }
    }

    long long delta = f(A, T, lower+1) - f(A, T, lower);


    for (int q = 0; q < Q; ++q) {
        int target;
        cin >> target;

        // cout << f(A, T, target) << endl;

        if (target >= upper) {
            cout << upVal << endl;
        } else if (target <= lower) {
            cout << lowVal << endl;
        } else {
            cout << lowVal + delta * (target - lower) << endl;
        }
    }


    return 0;
}