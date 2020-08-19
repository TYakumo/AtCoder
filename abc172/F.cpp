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

    cin >> N;

    vector <long long> A(N);
    long long xorSum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        xorSum ^= A[i];
    }

    xorSum ^= A[0]^A[1];
    // (A[0]-K) ^ (A[1]+K) ^ xorSum == 0 => Target
    // a+b = A[0]+A[1]
    // a+b = (a^b) + 2*(a&b)
    // (a^b) = xorSum
    long long R = A[0]+A[1] - xorSum;

    if (R%2 != 0 || R < 0) {
        cout << -1 << endl;
    } else {
        long long AND = R/2;

        // a+b = xorSum + 2*AND
        // a = (AND^Y)
        // b = (AND^Z)
        // Z^Y = xorSum
        if (AND & xorSum) {
            cout << -1 << endl;
        } else {
            // argMax(a) <= A[0] => argMin |A[0]-a|
            // 10^12 => (2^10)^4
            long long ans = AND;
            // cout << "BASE " << ans << endl;

            for (long long bit = 42; bit >= 0; --bit) {
                long long flag = (1LL << bit);
                if (flag & xorSum) { // dispatch
                    if (ans + flag <= A[0]) {
                        ans += flag;
                        // cout << "DEBUG ANS " << ans << endl;
                    }
                }
            }

            cout << (ans == 0 ? -1 : A[0]-ans) << endl;
        }
    }


    return 0;
}