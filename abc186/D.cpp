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

using VI = vector <int>;
using VLL = vector <long long>;

int main() {
    int N;

    cin >> N;
    VI A(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    VLL acc(N);
    acc[0] = A[0];
    for (int i = 1; i < N; ++i) {
        acc[i] = acc[i-1]+A[i];
    }

    long long ans = 0;

    for (int i = 0; i < N; ++i) {
        // from i+1 ... N-1
        long long sum = acc[N-1]-acc[i];
        long long len = N-1-(i+1)+1;
        long long minus = A[i]*len;

        ans += sum-minus;
    }

    cout << ans << endl;

    return 0;
}