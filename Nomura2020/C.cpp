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

const long long MAXD = 62;
const long long INF = 1LL<<MAXD;

long long upperBound(long long v) {
    if (v <= 0) {
        return 1;
    }

    if (v >= MAXD) {
        return INF;
    }

    return 1LL << v;
}

int main() {
    int N;
    cin >> N;

    vector <long long> A(N+1);
    vector <long long> NL(N+1);
    vector <long long> NLU(N+1, INF);

    for (int i = 0; i <= N; ++i) {
        cin >> A[i];
    }

    NLU[0] = 1 - A[0];

    for (int i = 1; i <= N; ++i) {
        NLU[i] = min(INF, NLU[i-1]*2 - A[i]);
    }

    // 2*NL[i] >= A[i+1] + NL[i+1] // two to one
    // NL[i] <= A[i+1] + NL[i+1] // one to one
    long long ans = A[N];
    for (int i = N-1; i >= 0; --i) {
        long long up = min(A[i+1] + NL[i+1], NLU[i]);
        long long low = (A[i+1] + NL[i+1] + 1) / 2;
        up = min(up, upperBound(i)-A[i]);

        // NL[i] + A[i] <= 2^i
        if ( up < low ||
            (i <= MAXD && low > (1LL << i)) ) {
            ans = -1;
            break;
        }

        // otherwise, it's feasible
        if (i <= MAXD) {
            NL[i] = min((1LL<<i), up);
        } else {
            NL[i] = up;
        }

        ans += (NL[i] + A[i]);
    }

    if (A[N] > upperBound(N)) {
        ans = -1;
    }

    cout << ans << endl;

    return 0;
}