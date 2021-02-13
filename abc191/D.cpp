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

const long long UNIT = 10000;

long long getLonglong() {
    string s;
    cin >> s;

    long long intVal = 0;
    long long floatVal = 0;
    int idx = 0;

    while (idx < s.size()) {
        if (s[idx] == '.') {
            ++idx;
            break;
        }

        intVal = intVal*10 + (s[idx++] - '0');
    }

    long long mul = UNIT/10;
    while (idx < s.size()) {
        floatVal += (s[idx++] - '0') * mul;
        mul /= 10;
    }

    return intVal * UNIT + floatVal;
}

int main() {
    // (X-x)^2 + (Y-y)^2 <= R^2
    // X^2 + x^2 - 2xX + Y^2 + y^2 - 2yY <= R^2
    const double eps = 0;
    long long IX = getLonglong();
    long long IY = getLonglong();
    long long IR = getLonglong();
    long long RR = (IR+UNIT-1)/UNIT*UNIT;

    IX = (IX%UNIT+UNIT)%UNIT;
    IY = (IY%UNIT+UNIT)%UNIT;

    long long ans = 0;
    long long GU = (IY+UNIT-1)/UNIT*UNIT;
    if (GU <= 0) {
        GU = UNIT;
    }

    for (long long x = -RR; x <= RR; x += UNIT) {
        long long rx = IX*IX + x*x - 2*x*IX;
        long long remain = IR*IR - rx;

        if (remain < 0) {
            continue;
        }

        // y^2 - 2yY + Y^2 <= remain
        // y^2 - 2yY - remain + Y^2 <= 0
        long long fr1 = -(RR+UNIT);
        long long cr2 = (RR+UNIT);
        auto calc = [&IY, &rx](long long y){ return y*y-2LL*y*IY+IY*IY; };

        long long low = GU;
        long long up = RR;

        while (low <= up) {
            long long mid = (low+up) / 2;
            mid = (mid/UNIT)*UNIT;

            if (calc(mid) <= remain) {
                fr1 = mid;
                low = mid+UNIT;
            } else {
                up = mid-UNIT;
            }
        }

        low = 0;
        up = RR;

        while (low <= up) {
            long long mid = (low+up) / 2;
            mid = (mid/UNIT)*UNIT;

            if (calc(-mid) <= remain) {
                cr2 = -mid;
                low = mid+UNIT;
            } else {
                up = mid-UNIT;
            }
        }

        if (fr1 >= GU) {
            ans += (fr1-GU)/UNIT+1;
        }

        if (cr2 <= 0) {
            ans += (-cr2)/UNIT+1;
        }
    }
    cout << ans << endl;

    return 0;
}