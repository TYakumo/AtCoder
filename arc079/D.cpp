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

using VLL = vector<long long>;

int main() {
    long long K;

    cin >> K;

    VLL ans;

    for (int n = 2; n <= 50; ++n) {
        const long long UPPER = 1000000000LL*10000000LL + 1000;
        // upperBound of K = Sum A[i] - 1
        long long sum = n*UPPER;

        if (sum-1 < K) {
            continue;
        }

        VLL A(n);
        long long mul = K/n;
        long long times = K-mul*n;

        for (int i = 0; i < n; ++i) {
            A[i] = i + mul;
        }

        int now = 0;
        for (int i = 0; i < times; ++i) {
            A[now] += n;

            for (int j = 0; j < n; ++j) {
                if (now != j) {
                    --A[j];
                }
            }

            now = (now+1) % n;
        }

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (A[i] > UPPER) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = A;
            break;
        }
    }

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); ++i) {
        if (i) {
            cout << " ";
        }

        cout << ans[i];
    }

    cout << endl;

    return 0;
}