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

using ll = long long;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

long long lcm(long long a, long long b) {
    return a*b / gcd(a, b);
}

int main() {
    long long N;
    cin >> N;

    long long l = 2;

    for (int v = 2; v <= N; ++v) {
        l = lcm(l, v);
    }

    long long res = 1;
    long long mul = max(0LL, (N-res+l-1)/l);
    long long ans = res+mul*l;

    cout << ans << endl;

    return 0;
}