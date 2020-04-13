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

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int main() {

    int K;
    long long ans = 0;

    cin >> K;

    for (int i = 1; i <= K; ++i) {
        for (int j = 1; j <= K; ++j) {
            for (int k = 1; k <= K; ++k) {
                ans += gcd(gcd(i, j), k);
            }
        }
    }

    cout << ans << endl;

    return 0;
}