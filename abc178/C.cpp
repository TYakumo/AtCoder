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

const long long MOD = 1000000000LL + 7;

long long modPow(long long v, long long p) {
    if (p == 0) {
        return 1;
    }

    long long hp = modPow(v, p/2);

    if (p%2) {
        return (hp*hp) % MOD * v % MOD;
    }
    return (hp*hp) % MOD;
}

int main() {
    // 10^N - 2 * 9^N + 8^N
    long long N;
    cin >> N;

    long long res = modPow(10, N) - 2*modPow(9, N) + modPow(8, N);
    res %= MOD;
    res += MOD;
    res %= MOD;

    cout << res << endl;

    return 0;
}