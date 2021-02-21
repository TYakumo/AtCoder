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

long long powMod(long long n, long long p, long long m) {
    if (p == 0) {
        return 1;
    }

    long long hp = powMod(n, p/2, m);
    long long ret = hp*hp%m;

    if (p%2 == 1) {
        ret = (ret*n)%m;
    }

    return ret;
}

int main() {
    long long A;
    long long B;
    long long C;
    cin >> A >> B >> C;
    A %= 10;

    if (A==5) {
        cout << 5 << endl;
    } else if (A%2 == 0) {
        // 2 => 4 => 8 => 6 => 2 ...
        // 4 => 6 => 4 ...
        // 6 => 6 ....
        // 8 => 4 => 2 => 6 => 8 ...
        long long ep = 4;

        if (A == 4) {
            ep = 2;
        } else if (A == 6) {
            ep = 1;
        }

        long long remain = powMod(B, C, ep);
        if (remain == 0) {
            remain = ep;
        }
        cout << powMod(A, remain, 10) << endl;
    } else {
        long long remain = powMod(B, C, 4);
        cout << powMod(A, remain, 10) << endl;
    }

    return 0;
}