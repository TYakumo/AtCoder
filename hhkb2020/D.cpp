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

const long long MOD = 1000000000 + 7;

int main() {
    int T;

    cin >> T;

    while (T--) {
        long long N;
        long long A;
        long long B;
        cin >> N >> A >> B;

        if (A < B) {
            swap(A, B);
        }

        long long tot = (N-A+1)*(N-A+1)%MOD*(N-B+1)%MOD*(N-B+1)%MOD;

        // Per Dimension Sigma i = {1 ... (B-1)} 2 * (N-(A+B-i)+1)
        // also (A+B-i) <= N => i >= (A+B) - N
        long long dimen = 0;
        if (A < N) {
            long long ABlen = B - max(1LL, A+B-N);
            dimen += 2*ABlen%MOD*(N+1)%MOD;
            long long ABbase = A+B-max(1LL, A+B-N);
            long long minus = (ABbase + (A+1)) % MOD * ABlen % MOD;
            dimen = (dimen-minus)%MOD;
        }
        dimen = (dimen + (N-A+1)*(A-B+1)%MOD)%MOD;

        long long all = dimen*dimen%MOD;
        tot -= all;
        tot = (tot%MOD+MOD)%MOD;

        cout << tot << endl;
    }


    return 0;
}