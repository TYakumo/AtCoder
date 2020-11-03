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
    int N;
    cin >> N;

    VLL A(N);
    long long sum = 0;

    // upperBound of K = Sum A[i] - 1
    // lowerBound of K = Sum A[i] - (N*(N-1))
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        sum += A[i];
    }

    // Sum A'[i] <= N*(N-1)
    // A'[i] = A[i] + K - chosen * (N+1); chosen = ceil{ (A[i]+K-N+1) / (N+1)}
    // K = Sum chosen(i)

    long long low = max(0LL, sum - N*(N-1));
    long long up = max(0LL, sum - 1);
    long long ans = 0;

    for (long long k = low; k <= up; ++k) {
        VLL B = A;

        for (int i = 0; i < N; ++i) {
            B[i] += k;
        }

        long long times = 0;
        for (int i = 0; i < N; ++i) {
            long long R = B[i]-N+1;
            times += (R+N)/(N+1);
        }

        if (times == k) {
            ans = times;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}