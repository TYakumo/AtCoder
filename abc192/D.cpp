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

string toBase(long long M, long long b) {
    string s;

    while (M) {
        long long maxVal = min(9LL, (M%b));
        if (M%b > 9) {
            for (int i = 0; i < s.size(); ++i) {
                s[i] = '9';
            }
        }
        s += (maxVal+'0');
        M /= b;
    }

    reverse(s.begin(), s.end());

    return s;
}

int main() {
    string X;
    long long M;
    cin >> X >> M;

    long long minb = 0;
    long long maxb = M;
    // d*B^X <= M => logd + X log B <= log M => X log B <= logM - logd
    reverse(X.begin(), X.end());
    for (int i = 0; i < X.size(); ++i) {
        long long digit = X[i]-'0';
        minb = max(minb, digit+1LL);
    }

    if (X.size() == 1) { //only one digit
        maxb = minb;
    }

    long long low = minb;
    long long up = maxb;
    long long ans = minb-1;

    reverse(X.begin(), X.end());

    while (low <= up) {
        long long mid = (low+up) / 2;

        bool ok = true;

        string MS = toBase(M, mid);

        if (MS.size() < X.size() || (MS.size() == X.size() && MS < X)) {
            ok = false;
        }

        if (ok) {
            low = mid+1;
            ans = mid;
        } else {
            up = mid-1;
        }
    }

    cout << (ans-minb)+1 << endl;

    return 0;
}