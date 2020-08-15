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
    const long long INF = 100000000LL * 100000000LL;
    long long X;
    long long K;
    long long D;
    long long ans = INF;

    cin >> X >> K >> D;
    long long maxMove = min(abs(X/D), K);
    K -= maxMove;

    if (X < 0) {
        X += maxMove*D;

        if (K%2 != 0) {
            ans = abs(X+D);
        } else {
            ans = abs(X);

            if (K >= 2) {
                ans = min(ans, abs(X+2*D));
            }
        }
    } else {
        X -= maxMove*D;

        if (K%2 != 0) {
            ans = abs(X-D);
        } else {
            ans = abs(X);

            if (K >= 2) {
                ans = min(ans, abs(X-2*D));
            }
        }
    }

    cout << ans << endl;


    return 0;
}