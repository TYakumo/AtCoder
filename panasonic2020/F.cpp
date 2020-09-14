#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

const int MAXD = 35;

inline bool checkCross(long long dblk1, long long dblk2) {
    if (dblk2 - dblk1 >= 3) {
        return true;
    } else {
        for (long long y = dblk1+1; y < dblk2; ++y) {
            if (y % 3 == 1) {
                return true;
            }
        }
    }
    return false;
}

inline long long getDist(long long div, long long a, long long b, long long da, long long db) {
    long long blk1 = a / div;
    long long blk2 = b / div;

    long long dblk1 = da / div;
    long long dblk2 = db / div;

    if (blk1 == blk2 && blk1%3 == 1 && checkCross(min(dblk1, dblk2), max(dblk1, dblk2))) {
        long long from = blk1 * div - 1;
        long long to = (blk1+1) * div;
        return min(abs(a-from)+abs(b-from), abs(a-to)+abs(b-to));
    }

    return abs(a-b);
}

inline long long solve(long long a, long long b, long long c, long long d) {
    long long bx = abs(a-c);
    long long by = abs(b-d);
    long long dx = bx;
    long long dy = by;
    long long div = 1;

    for (int i = 0; i < MAXD; ++i) {
        dx = max(dx, getDist(div, a, c, b, d));
        dy = max(dy, getDist(div, b, d, a, c));

        div *= 3;
    }

    return max(dx + by, bx + dy);
}

int main() {
    int Q;
    cin >> Q;

    while (Q--) {
        long long a;
        long long b;
        long long c;
        long long d;

        cin >> a >> b >> c >> d;
        cout << solve(a-1, b-1, c-1, d-1) << endl;
    }

    return 0;
}