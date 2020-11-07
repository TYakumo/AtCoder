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

long long findLimit(long long N, long long CP, long long P) {
    --P;
    --CP;

    long long ans = 0;
    // argmin max value of prod [N+1 ... (N+v)] x [1 ... v] => reverse matching max{(N+v)*1 ... ,(N+2)*(v-1), (N+1)*v}
    // f(x) = (N+v-x)*(x) = Nx+vx-x^2, f'(x) = 0 => N+v-2x = 0
    long long low = 1;
    long long up = CP;

    while (low <= up) {
        long long mid = (low + up) / 2;
        long long res = (N+mid-1+1)*1;

        long long tryMax = min((N+mid+1)/2, mid);
        for (long long val = max(1LL, tryMax-2); val <= tryMax+2 && val <= CP; ++val) {
            res = max(res, (N+mid-val+1)*val);
        }

        if (res <= P) {
            low = mid+1;
            ans = mid;
        } else {
            up = mid-1;
        }
    }

    return ans;
}

int main() {
    int Q;

    cin >> Q;

    while (Q--) {
        VLL A(2);
        VLL C(2);

        cin >> A[0] >> A[1];

        long long P = A[0] * A[1];
        long long ans = 0;
        for (int i = 0; i < 2; ++i) {
            C[i] = findLimit(A[i^1], A[i], P);
        }

        ans = C[0] + C[1];
        // check [C[0]+1, A[0]) matching with [C[1]+1, A[1])
        long long num = max(0LL, min(A[0]-1-C[0], A[1]-1-C[1]));
        ans += num;

        cout << ans << endl;
    }

    return 0;
}