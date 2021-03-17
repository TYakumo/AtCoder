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
    long long B;
    long long C;
    cin >> B >> C;

    long long ans = 1; // do nothing

    if (B > 0 && C >= 1) {
        if (C > 0) {
            if (C/2 >= abs(B)) {
                ans += 2*(abs(B)-1)+1;
            } else {
                ans += 2*(C/2);

                if (C%2 == 0) {
                    --ans;
                }
            }
        }

        --C;
        B *= -1;
        ++ans;
    } else if (B == 0 && C >= 2) {
        C -= 2;
        B = -1;
        ++ans;

        if (C > 0) { // mirror
            ++ans;
        }
    } else if (B < 0) {
        long long tmpC = C-1;
        ++ans;

        if (tmpC > 0) {
            if (tmpC/2 >= abs(B)) {
                ans += 2*(abs(B)-1)+1;
            } else {
                ans += 2*(tmpC/2);

                if (tmpC%2 == 0) {
                    --ans;
                }
            }
        }
    }

    if (C > 0) {
        long long maxdist = C/2;
        ans += maxdist*2;
        if (C%2 == 0) {
            --ans;
        }
    }

    cout << ans << endl;

    return 0;
}