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
    int R1;
    int C1;
    int R2;
    int C2;

    cin >> R1 >> C1;
    cin >> R2 >> C2;

    int dr = abs(R2-R1);
    int dc = abs(C2-C1);

    if (dc > dr) {
        swap(dr, dc);
    }

    if (dr == 0 && dc == 0) {
        cout << 0 << endl;
    } else if (dr+dc <= 3 || dr==dc) {
        cout << 1 << endl;
    } else if ((dr-dc)%2 == 0 || (dr-dc) <= 3 || (dr+dc) <= 6) { // dy1+dy2=x, dy1-dy2=y; do something => dr==dc
        cout << 2 << endl;
    } else {
        // (dr/2, dr/2), (dr/2, -dr/2) => (floor(dr/2), 0) or (floor(dr/2), any)
        cout << 3 << endl;
    }

    return 0;
}