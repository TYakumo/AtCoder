#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    cin >> N;

    VLL A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());
    long double ans = (long double)A.back()/2.0*N;
    VLL sum(N);
    sum[0] = A[0];
    for (int i = 1; i < N; ++i) {
        sum[i] = sum[i-1]+A[i];
    }

    // 2x >= Ai => x+Ai - min(Ai, 2x) = x
    // 2x < Ai => x+Ai - 2x = Ai-x
    // for x => sigma (1...j) x + sigma (j+1...N) Aj-x
    for (int i = 1; i < N; ++i) {
        long long left = i;
        long long right = N-i;

        if (left < right) {
            long double x = A[i]/2.0;
            long double res = x*(left-right) + sum.back() - sum[i-1];
            ans = min(ans, res);

        } else {
            long double x = A[i-1]/2.0;
            long double res = x*(left-right) + sum.back() - sum[i-1];
            ans = min(ans, res);
        }
    }

    ans /= N;
    cout << setprecision(15) << fixed << ans << endl;
    return 0;
}