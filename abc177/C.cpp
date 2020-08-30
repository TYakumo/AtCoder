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
    const long long MOD = 1000000000 + 7;
    long long sum = 0;
    long long ans = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        sum += A[i];
    }

    for (int i = 0; i < A.size(); ++i) {
        sum -= A[i];
        sum %= MOD;

        ans += (A[i] * sum)%MOD;
        ans %= MOD;
    }

    cout << (ans + MOD)% MOD << endl;

    return 0;
}