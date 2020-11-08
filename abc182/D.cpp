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

int main() {
    int N;
    cin >> N;

    VLL A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    long long sum = 0;
    long long cur = 0;
    long long ans = 0;
    long long maxPrefix = 0;

    for (int i = 0; i < N; ++i) {
        sum += A[i];
        maxPrefix = max(maxPrefix, sum);
        ans = max(ans, cur+maxPrefix);

        cur += sum;
    }

    cout << ans << endl;

    return 0;
}